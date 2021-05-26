/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    EZI2C_Start();  // Tune capsense sensors with I2C

    EZI2C_EzI2CSetBuffer1(
                      sizeof(CapSense_dsRam),
                      sizeof(CapSense_dsRam),
                      (uint8 *) &CapSense_dsRam 
                     );
    
    CapSense_Start();
    
    CapSense_ScanAllWidgets();
    
    for(int i = 0; i < 5; i++)
    {
        ledPin2_Write(1);
        ledPin_Write(1);
        CyDelay(100);
        ledPin2_Write(0);
        ledPin_Write(0);
        CyDelay(100);
    }
    
    for(;;)
    {
        if(CapSense_IsBusy() == CapSense_NOT_BUSY)
        {
            CapSense_RunTuner();
            CapSense_ScanAllWidgets();
        }
    }
}

/* [] END OF FILE */
