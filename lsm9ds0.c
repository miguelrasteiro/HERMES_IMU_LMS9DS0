 /**
  * \addtogroup lsm9ds0
  * \{
  * \file lsm9ds0.c
  * \author Miguel Rasteiro \n\t
  * \brief LSM9DS0 basic driver \n
  * \version  Version 1.0 Release 1 \n
  * \date     29 de January de 2014, 10:14 \n\n
  * \ref license \n\n
  *    Change History:
  * ************************************************************************
  * | VERSION      | DATE	    | AUTHORS	  | DESCRIPTION            |
  * |:------------:|:--------------:|:------------|:-----------------------|
  * | 1.0          |   29/1/2014    | MR          | First Release          |
  * \n\n
  * \section lsm9ds0code LSM9DS0 Source Code
  * \code
  */
#include "lsm9ds0.h"
#include <peripheral/i2c.h>
#include <plib.h>


/*******************************************************************************
 * Function Name	: WriteRegister
 * Description		: Generic Writing function.
 * Input		: Sensor Address, Register Address, Data to be written
 * Output		: None
 * Return		: None
 *******************************************************************************/
void WriteRegister ( UINT8 add, UINT8 reg, UINT8 data ) {

    StartI2C1();                //Send the Start Bit
    IdleI2C1();                 //Wait to complete
    MasterWriteI2C1 (add );
    IdleI2C1();                 //Wait to complete
    MasterWriteI2C1 (reg );
    IdleI2C1();                 //Wait to complete
    MasterWriteI2C1 (data);
    IdleI2C1();                 //Wait to complete
    StopI2C1();                 //Send the Stop condition
    IdleI2C1();                 //Wait to complete
}

/*******************************************************************************
* Function Name		: ReadRegister
* Description		: Generic Reading function.
* Input			: Sensor Address, Register Address
* Output		: Data Read
* Return		: None
*******************************************************************************/
void ReadRegister  ( UINT8 add, UINT8 reg, UINT8* data ) {

    StartI2C1();                        //Send the Start Bit
    IdleI2C1();                         //Wait to complete
    MasterWriteI2C1 (( add|Write ));
    IdleI2C1();                         //Wait to complete
    MasterWriteI2C1 ( reg );            //transmit read command
    IdleI2C1();                         //Wait to complete
    StartI2C1();                        //Send the Start Bit
    IdleI2C1();                         //Wait to complete
    MasterWriteI2C1 (( add|Read ));
    IdleI2C1();                         //Wait to complete
    *data = MasterReadI2C1 ();
    IdleI2C1();                         //Wait to complete
    StopI2C1();                         //Send the Stop condition
    IdleI2C1();                         //Wait to complete
}

/**
 *  @brief  Write to device using generic i2c protocol
 *  @param[in]  slave_addr - slave address
 *  @param[in]  reg_addr   - register address
 *  @param[in]  length     - number of bytes to write
 *  @param[in]  *data      - pointer for data to write
 *  @return     0 if sucessfull, 1 otherwise
 */
int i2c_write(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char const *data) {

	BYTE i;

	StartI2C1();								//Send the Start Bit
	IdleI2C1();									//Wait to complete
        if (MasterWriteI2C1(slave_addr|Write ))
            return 1;
	IdleI2C1();
        if (MasterWriteI2C1(reg_addr))
            return 1;
	IdleI2C1();

	for(i=0;i<length;i++){
            if (MasterWriteI2C1(data[i]))
                return 1;
	}
        StopI2C1();								//Send the Stop condition
        IdleI2C1();								//Wait to complete

	return 0;
}

/**
 *  @brief  Write to device using generic i2c protocol
 *  @param[in]  slave_addr - slave address
 *  @param[in]  reg_addr   - register address
 *  @param[in]  length     - number of bytes to read
 *  @param[in]  *data      - pointer to where register data is to be transfered
 *  @return     0 if sucessfull, 1 otherwise
 */
int i2c_read(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char *data) {

	BYTE i=2;

	StartI2C1();								//Send the Start Bit
	IdleI2C1();
        if (MasterWriteI2C1((slave_addr|Write )))
            return 1;
	IdleI2C1();
        if (MasterWriteI2C1(reg_addr))
            return 1;
	IdleI2C1();
        StartI2C1();                        //Send the Start Bit
        IdleI2C1();                         //Wait to complete
        if (MasterWriteI2C1((slave_addr|Read )))
            return 1;
	IdleI2C1();
	//I2CReceiverEnable ( I2C1, TRUE);

	for(i=0;i<length;i++) {
            data[i] = MasterReadI2C1();
		if(i<(length-1)) {
                    I2CAcknowledgeByte(I2C1, TRUE);
                   // IdleI2C1();
		}
		else {
                    I2CAcknowledgeByte(I2C1, FALSE);
                   // IdleI2C1();
		}
	}
        StopI2C1();								//Send the Stop condition
        IdleI2C1();								//Wait to complete

	return 0;
}

/*******************************************************************************
* Function Name  : ReadGyroRaw
* Description    : Read the angular velocity values Output Registers
* Input          : Raw_gyro axis
* Output         : x,y,z 16 bits raw_data
* Return         : None
*******************************************************************************/
void ReadGyroRaw ( sensor_xyz* raw ) {

    UINT8 data[6];
    sensor_xyz raw2;

    i2c_read(Address_G, OUT_X_L_G, 6, data);
    raw->x = ( data[1] <<8 | data[0] );
    raw->y = ( data[3] <<8 | data[2] );
    raw->z = ( data[5] <<8 | data[4] );

    raw2.x =  data[1] <<8 ;
    raw2.x|=  data[0] ;
    raw2.y = ( data[3] <<8 | data[2] );
    raw2.z = ( data[5] <<8 | data[4] );

//    UINT8   L_value, H_value;
//
//    ReadRegister ( Address_G, OUT_X_L_G, &L_value );
//    ReadRegister ( Address_G, OUT_X_H_G, &H_value );
//    raw->x = ( H_value <<8 | L_value );
//
//    ReadRegister ( Address_G, OUT_Y_L_G, &L_value );
//    ReadRegister ( Address_G, OUT_Y_H_G, &H_value );
//    raw->y = ( H_value <<8 | L_value );
//
//    ReadRegister ( Address_G, OUT_Z_L_G, &L_value );
//    ReadRegister ( Address_G, OUT_Z_H_G, &H_value );
//    raw->z = ( H_value <<8 | L_value );
}

/*******************************************************************************
* Function Name  : ReadAccRaw
* Description    : Read the accelaration values Output Registers
* Input          : Raw_acc axis
* Output         : x,y,z raw_data
* Return         : None
*******************************************************************************/
void ReadAccRaw  ( sensor_xyz* raw ) {

    UINT8 data[6];

    i2c_read(Address_XM, OUT_X_L_A, 6, data);
    raw->x = ( data[1] <<8 | data[0] );
    raw->y = ( data[3] <<8 | data[2] );
    raw->z = ( data[5] <<8 | data[4] );

//    UINT8   L_value, H_value;
//
//    ReadRegister ( Address_XM, OUT_X_L_A, &L_value );
//    ReadRegister ( Address_XM, OUT_X_H_A, &H_value );
//    raw->x = ( H_value <<8 | L_value );
//
//    ReadRegister ( Address_XM, OUT_Y_L_A, &L_value );
//    ReadRegister ( Address_XM, OUT_Y_H_A, &H_value );
//    raw->y = ( H_value <<8 | L_value );
//
//    ReadRegister ( Address_XM, OUT_Z_L_A, &L_value );
//    ReadRegister ( Address_XM, OUT_Z_H_A, &H_value );
//    raw->z = ( H_value <<8 | L_value );
}

/*******************************************************************************
* Function Name  : ReadMagRaw
* Description    : Read the magnetic values Output Registers
* Input          : Raw_mag axis
* Output         : x,y,z raw_data
* Return         : None
*******************************************************************************/
void ReadMagRaw  ( sensor_xyz* raw ) {


    UINT8 data[6];

    i2c_read(Address_XM, OUT_X_L_M, 6, data);
    raw->x = ( data[1] <<8 | data[0] );
    raw->y = ( data[3] <<8 | data[2] );
    raw->z = ( data[5] <<8 | data[4] );

//    UINT8   L_value, H_value;
//
//    ReadRegister ( Address_XM, OUT_X_L_M, &L_value );
//    ReadRegister ( Address_XM, OUT_X_H_M, &H_value );
//    raw->x = ( H_value <<8 | L_value );
//
//    ReadRegister ( Address_XM, OUT_Y_L_M, &L_value );
//    ReadRegister ( Address_XM, OUT_Y_H_M, &H_value );
//    raw->y = ( H_value <<8 | L_value );
//
//    ReadRegister ( Address_XM, OUT_Z_L_M, &L_value );
//    ReadRegister ( Address_XM, OUT_Z_H_M, &H_value );
//    raw->z = ( H_value <<8 | L_value );
}

/*******************************************************************************
* Function Name  : ReadTemp
* Description    : Read the temperature values Output Registers
* Input          : Temperature pointer
* Output         : Temperature_raw
* Return         : None
*******************************************************************************/
void ReadTemp ( short* temp ) {

    UINT8   L_value, H_value;

    ReadRegister ( Address_XM, OUT_TEMP_L_XM, &L_value );
    ReadRegister ( Address_XM, OUT_TEMP_H_XM, &H_value );
    * temp = ( H_value <<8 | L_value );
}

/*******************************************************************************
* Function Name  : GetGyroAddr
* Description    : Get Gyroscope Address
* Input          : None
* Output         : None
* Return         : uint_8 Addr
*******************************************************************************/
UINT8 GetGyroAddr ( void ) {

    ReadRegister (Address_G, WHO_AM_I_G, &buff[0] );
    return buff[0];
}

/*******************************************************************************
* Function Name  : GetAccMagAddr
* Description    : Get XM module Address
* Input          : None
* Output         : None
* Return         : uint_8 Addr
*******************************************************************************/
UINT8 GetAccMagAddr ( void ) {

    ReadRegister (Address_XM, WHO_AM_I_XM, &buff[0] );
    return buff[0];
}

/*******************************************************************************
* Function Name  : GyroEnable
* Description    : Enable Gyroscope
* Commands       : GYRO_OFF         - Turn-off gyro module 
*                  GYRO_ON          - Normal Power mode
*                  ENABLE_ALL_AXES  - Enable all Gyro axis
*                  X_ENABLE         - Enable  X  Gyro axis
*                  Y_ENABLE         - Enable  Y  Gyro axis
*                  Z_ENABLE         - Enable  Z  Gyro axis
*                  BW00             - Defines cut-off according to ODR (See Datasheet)
*                  BW01             - Defines cut-off according to ODR
*                  BW10             - Defines cut-off according to ODR
*                  BW11             - Defines cut-off according to ODR
*                  G_ODR095         - ODR =  95Hz
*                  G_ODR190         - ODR = 190Hz
*                  G_ODR380         - ODR = 380Hz
*                  G_ODR760         - ODR = 760Hz
*            -> OR condition between command type
* Input          : Command
* Output         : None
* Return         : None
*******************************************************************************/
void GyroEnable ( char command ){

    WriteRegister ( Address_G, CTRL_REG1_G, command );
}

/*******************************************************************************
* Function Name  : GyroConfig
* Description    : Configure Gyroscope
* Commands       : FS_245_DPS        - Set 245  dps Full-scale
*                  FS_500_DPS        - Set 500  dps Full-scale
*                  FS_2000_DPS       - Set 2000 dps Full-scale
*                  LITTLE_ENDIAN     - Little Endian Data Output
*              	   BIG_ENDIAN	     - Big Endian Data Output
*       	   CONTINUOUS_UPDATE - Continuous Block Update
*       	   BDU_G_ENABLE      - Output registers not updated until MSb and LSb read
*            -> OR condition between command type
* Input          : Command
* Output         : None
* Return         : None
*******************************************************************************/
void GyroConfig ( char command ){

    WriteRegister ( Address_G, CTRL_REG4_G, command );
}

/*******************************************************************************
* Function Name  : AccEnableConfig
* Description    : Enable and Configure Accelerometer
* Command1       : ACC_OFF          - OFF
*                  A_ODR3_125       - Acelerometer Data Rate = 3.125Hz
*                  A_ODR6_25        - ODR = 6.25Hz
*                  A_ODR12_5        - ODR = 12.5Hz
*                  A_ODR25          - ODR = 25Hz
*                  A_ODR50          - ODR = 50Hz
*                  A_ODR100         - ODR = 100Hz
*                  A_ODR200         - ODR = 200Hz
*                  A_ODR400         - ODR = 400Hz
*                  A_ODR800         - ODR = 800Hz
*                  A_ODR1600        - ODR = 1600Hz
*                  CONTINUOUS_UPDATE- Continuous block update
*                  BDU_A_ENABLE     - Output registers not updated until MSb and LSb read
*                  ENABLE_ALL_AXES  - Enable all Acc axis
*                  X_ENABLE         - Enable  X  Acc axis
*                  Y_ENABLE         - Enable  Y  Acc axis
*                  Z_ENABLE         - Enable  Z  Acc axis
*            -> OR condition between command type
* Command2       : FS_2_G           - Set 2 g Full-scale
*                  FS_4_G           - Set 4 g Full-scale
*                  FS_6_G           - Set 6 g Full-scale
*                  FS_8_G           - Set 8 g Full-scale
*                  FS_16_G          - Set 16g Full-scale
*            -> OR condition between command type
* Input          : command1, command2
* Output         : None
* Return         : None
*******************************************************************************/
void AccEnableConfig ( char command1, char command2 ){

    WriteRegister ( Address_XM, CTRL_REG1_XM, command1 );
    WriteRegister ( Address_XM, CTRL_REG2_XM, command2 );
}

/*******************************************************************************
* Function Name  : MagEnableConfig
* Description    : Enable and Configure Magnetometer
* Command1       : M_ODR3_125       - Magnetometer Data Rate = 3.125Hz
*                  M_ODR6_25        - ODR = 6.25Hz
*                  M_ODR12_5        - ODR = 12.5Hz
*                  M_ODR25          - ODR = 25Hz
*                  M_ODR50          - ODR = 50Hz
*                  M_ODR100         - ODR = 100Hz Only if Accelerometer ODR>50Hz
*                  HIGH_MAG_RES     - High magnetic resolution
*                  LOW_MAG_RES      - LOW magnetic resolution
*                  TEMP_EN          - Enable Temperature sensor
*            -> OR condition between command type
* Command2       : FS_2_GAUSS       - Set 2 gauss Full-scale
*                  FS_4_GAUSS       - Set 4 gauss Full-scale
*                  FS_8_GAUSS       - Set 6 gauss Full-scale
*                  FS_16_GAUSS      - Set 16gauss Full-scale
*            -> OR condition between command type
* Input          : command1, command2
* Output         : None
* Return         : None
*******************************************************************************/
void MagEnableConfig ( char command1, char command2 ){

ReadRegister (Address_XM, WHO_AM_I_XM, &buff[0] );
    WriteRegister ( Address_XM, CTRL_REG5_XM, 0x00 );
ReadRegister (Address_XM, CTRL_REG5_XM, &buff[0] );
    WriteRegister ( Address_XM, CTRL_REG5_XM, command1 );
ReadRegister (Address_XM, CTRL_REG5_XM, &buff[0] );

    WriteRegister ( Address_XM, CTRL_REG6_XM, command2 );
    WriteRegister ( Address_XM, CTRL_REG7_XM, 0B00000000 );
}
/**\endcode \}*/