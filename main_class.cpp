
#include "main_class.h"
#include "version.h"
#include "ipc.h"



#include <unistd.h>


CMain::CMain() {
}


CMain::~CMain() {
	OscDestroy();
}



OSC_ERR CMain::Init(int argc, char ** argv) {
	
	OSC_ERR err;
	

	/******* Create the framework **********/
	if((err=OscCreate(
			&OscModule_log, 
			&OscModule_sup, 
			&OscModule_bmp, 
			&OscModule_cam,  
			&OscModule_vis
			//,&OscModule_gpio
			))!=SUCCESS)
		return(err);
	
	
	OscLogSetConsoleLogLevel(INFO);
	OscLogSetFileLogLevel(WARN);
	
	//OscGpioConfigSensorLedOut(true);
	
#if defined(OSC_HOST) || defined(OSC_SIM)
	{
		void * hFileNameReader;
		
		if((err=OscFrdCreateConstantReader(&hFileNameReader, TEST_IMAGE_FN))!=SUCCESS)
			return(err);
		if((err=OscCamSetFileNameReader(hFileNameReader))!=SUCCESS)
			return(err);
	}
#endif /* OSC_HOST or OSC_SIM */
	

	/* init the camera */
	if((err=m_camera.Init(ROI(), 3))!=SUCCESS)
		return(err);
	
	m_camera.setAutoExposure(true);
	
	
	char* osc_version;
	OscGetVersionString(&osc_version);
	string welcome_msg="###  "APP_NAME" "+getAppVersion().toStr()+"  OSCAR "+osc_version+"  ###\n";
	OscLog(INFO, welcome_msg.c_str());
	
	
	return(SUCCESS);
}

OSC_ERR CMain::MainLoop() {
	OSC_ERR err=SUCCESS;
	
	CIPC ipc(m_camera);
	err=ipc.Init();
	
	OscSimInitialize();
	
	/* read one image ahead */
	m_camera.CapturePicture();
	m_camera.ReadPicture();
	
	printf("read\n");
	
	uint32 startCyc=OscSupCycGet();
	
	while(err==SUCCESS) { /* infinite loop if no error occurs */
		
		err=ipc.handleIpcRequests();
		
		/* Allow other processes to run. Due to kernel tick rate of 250Hz this
		 * call will return in 4ms. */
		usleep(500);
		
		/* Advance the simulation step counter. */
		OscSimStep();
		
		
		uint32 delta_time_us=OscSupCycToMicroSecs(OscSupCycGet() - startCyc);
		if(delta_time_us/1000 > 1000) {
			startCyc=OscSupCycGet();
			if(ipc.img_count > 0)
				printf("Sent %i images in %i ms\n", ipc.img_count, (int) delta_time_us/1000);
			ipc.img_count=0;
		}
	}
	return(err);
}



