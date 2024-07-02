# Backward Chained Behavior Trees, BCBT_D
The BCBT_D is developed based on https://btirai.github.io/youbot.  
## Run in Linux:  
1. Install Dependencies:  
    &emsp;Open terminal:  
         &emsp; &emsp;sudo apt-get install build-essential libgl1-mesa-dev python3-tk qtdeclarative5-dev
2. Download & install V-REP(CoppeliaSim):  
    &emsp;https://www.coppeliarobotics.com/previousVersions (Recommended version: 3.6.2)  
3. Compile BCBT_D:  
    &emsp;cd BCBT_D  
    &emsp;mkdir build & cd build  
    &emsp;cmake ..  
    &emsp;make  
4. Run V-REP:  
    &emsp;Open terminal:  
        &emsp;&emsp;go to V-REP directory  
        &emsp;&emsp;./vrep.sh  
        &emsp;&emsp;File->Open Scene:  
        &emsp;&emsp;BCBT_D/object_sort_task.ttt  
5. Run BCBT_D:  
    &emsp;Open terminal:  
         &emsp;&emsp;cd BCBT_D/build  
         &emsp;&emsp;./BT 
         &emsp;&emsp;File->Load XML 
         &emsp;&emsp;BCBT_D/objectsort.xml 
         &emsp;&emsp;Press play icon 
