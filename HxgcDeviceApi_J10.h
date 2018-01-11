//HxgcDeviceApi_J10.h
#ifndef _HXGC_DEVICE_API_J10_H_
#define _HXGC_DEVICE_API_J10_H_
/*返回错误定义*/
/*        
  -1            //读卡器联接失败
  -2            //参数错误
  -3            //设备类型错误
  0                //成功
  0x1001        //不支持接触式用户卡
  0x1002        //接触式用户卡未插到位
  0x1003        //接触式用户卡已上电
  0x1004        //接触式用户卡未上电
  0x1005        //接触式用户卡上电失败
  0x1006        //操作接触式用户卡数据无回应
  0x1007        //操作接触式用户卡数据出现错误
  0x2001        //不支持PSAM卡
  0x2002        //PSAM卡未插到位
  0x2003        //PSAM卡已上电
  0x2004        //PSAM卡未上电
  0x2005        //PSAM卡上电失败
  0x2006        //操作PSAM卡数据无回应
  0x2007        //操作PSAM卡数据出现错误
  0x3001        //不支持非接触式用户卡
  0x3002        //未检测到非接触式用户卡
  0x3003        //非接触式用户卡已激活
  0x3004        //非接触式用户卡未激活
  0x3005        //非接触式用户卡激活失败
  0x3006        //操作非接触式用户卡超时
  0x3007        //操作非接触式用户卡数据出现错误
  0x3008        //非接触式用户卡停活失败
  0x3009        //有多张卡在感应区
  0x4001        //不支持磁条卡
  0x4006        //操作磁条超时
  0x4007        //操作磁条数据出现错误
*/

/*二代证返回错误定义*/
/*
    0x90  //成功                                                        

    0x91  //卡中无此内容                                                
    0x9F  //寻卡成功                                                    

    0x01  //端口打开失败                                                
    0x02  //接收卡数据超时                                              
    0x03  //数据传输错误                                                
    0x05  //该SAM_V串口不可用, 只有咋SDT_GetCOMBaud时才有可能返回.      
    0x09  //打开文件失败.                                               
    0x10  //接收业务终端数据的校验和错.                                 
    0x11  //接收业务终端数据的长度错.                                   
    0x21  //接收业务终端的命令错误, 包括命令中的各种树枝或逻辑搭配错误. 
    0x23  //越权操作.                                                   
    0x24  //无法识别的错误.                                             
    0x80  //寻卡失败.                                                   
    0x81  //选卡失败.                                                   
    0x31  //卡认证SAM_V失败.                                            
    0x32  //SAM_V认证卡失败.                                            
    0x33  //信息验证错误.                                               
    0x37  //指纹信息验证失败.                                           
    0x3F  //信息长度错误.                                               
    0x40  //无法识别的卡类型.                                           
    0x41  //读卡失败.                                                   
    0x47  //取随机数失败.                                               
    0x60  //SAM_V自检失败, 不能接收指令.                                
    0x66  //SAM_V没有经过授权, 无法使用.                                
*/

extern "C"{

/*--------------------------------------以下为设备通讯基本函数API----------------------------------------*/

/*
函数声明    int CarderOpen( int pi_iPort, int pi_iBaud = 115200 ) 
功能描述    打开设备。
参数含义    pi_iPort：输入参数，
                      1~16 串口；
                      1001~1016 USB口；缺省的一个USB设备端口号为1001。
            pi_iBaud：输入参数，波特率，默认为115200bps；USB设备该参数无效。
返回值        0 成功 -1失败
*/
int __stdcall CarderOpen( int pi_iPort, int pi_iBaud = 115200 );


/*
函数声明    CarderClose( )
功能描述    关闭设备。
参数含义    无
返回值        0 成功 -1失败
*/
int __stdcall CarderClose();


/*
函数声明    int GetModuleVer( int pi_iModule, unsigned char* po_pszModuleVer )
功能描述    获取设备版本信息。
参数含义    pi_iModule：输入参数，
                        0 接触式IC卡模块；
                        1 非接触式卡模块。
            po_szModuleVer：输出参数，模块版本信息。
返回值        0 成功　<0失败
*/
int __stdcall GetModuleVer( int pi_iModule, unsigned char* po_pszModuleVer );


/*
函数声明    int CarderBeeping( unsigned char pi_bySustainedTime, unsigned char pi_byIntervalTime, unsigned char pi_byTimes )
功能描述    读卡器蜂鸣器控制。
参数含义    pi_bySustainedTime：输入参数，单次鸣叫持续时间, 单位100毫秒。
            pi_byIntervalTime：输入参数，鸣叫间隔时间, 单位100毫秒。
            pi_byTimes：输入参数，蜂鸣器鸣叫次数。
返回值        0 成功　!=0 错误号
*/
int __stdcall CarderBeeping( unsigned char pi_bySustainedTime, unsigned char pi_byIntervalTime, unsigned char pi_byTimes );


/*--------------------------------------以下为CPU卡API-----------------------------------------*/
/*
函数声明    int GetCardStatus( unsigned char pi_bySlot );
功能描述    取卡片状态。
参数含义    pi_bySlot： 输入参数，卡槽号，
                        0xFF 非接触式卡；
                        0x00〜0x0F 接触式CPU卡1〜卡16；
                        0x10〜0x1F SAM卡1〜卡16。
返回值        -1失败 >0 状态号或错误号
*/
int __stdcall GetCardStatus( unsigned char pi_bySlot );


/*
函数声明    int CardActive( unsigned char pi_bySlot, unsigned char* po_pbysATR, int* po_piATRSize );
功能描述    CPU卡上电复位。
参数含义    pi_bySlot： 输入参数，卡槽号，
                        0xFF 非接触式卡；
                        0x00〜0x0F 接触式CPU卡1〜卡16；
                        0x10〜0x1F SAM卡1〜卡16。
            po_pbysATR：输出参数，当卡前卡槽为接触式卡或SAM卡卡片时为 卡片ATR数据； 
                        为非接卡时为 卡类型(1Byte = 0x0A TYPE A, = 0x0B TYPE A) + 卡片UID长度(1Byte) + 卡片UID + 卡片ATR数据。
            po_piATRSize：输出参数，ATR数据长度。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall CardActive( unsigned char pi_bySlot, unsigned char* po_pbysATR, int* po_piATRSize );


/*
函数声明    int CardDeActive( unsigned char pi_bySlot );
功能描述    CPU卡下电。
参数含义    pi_bySlot： 输入参数，卡槽号，
            0xFF 非接触式卡；
            0x00〜0x0F 接触式CPU卡1〜卡16；
            0x10〜0x1F SAM卡1〜卡16。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall CardDeActive( unsigned char pi_bySlot );


/*
函数声明    int CardAPDU(   unsigned char pi_bySlot, 
                            unsigned char* pi_pbysSendApdu, 
                            int pi_iSendSize, 
                            unsigned char* po_pbysRecvApdu, 
                            int* po_piRecvSize, 
                            double pi_dOutTime );
功能描述    CPU卡APDU交互。
参数含义    pi_bySlot： 输入参数，卡槽号，
                        0xFF 非接触式卡；
                        0x00〜0x0F 接触式CPU卡1〜卡16；
                        0x10〜0x1F SAM卡1〜卡16。
            pi_pbysSendApdu：输入参数，APDU数据。
            pi_iSendSize：输入参数，APDU数据长度。
            po_pbysRecvApdu：输出参数，卡片响应数据。
            po_piRecvSize：输出参数，卡片响应数据长度。
            pi_dOutTime:输入参数，操作超时时间，单位：秒。
返回值        0 成功　-1通讯失败 >0错误号
*/
int  __stdcall CardAPDU(unsigned char pi_bySlot, 
                        unsigned char* pi_pbysSendApdu, 
                        int pi_iSendSize, 
                        unsigned char* po_pbysRecvApdu, 
                        int* po_piRecvSize, 
                        double pi_dOutTime );


/*--------------------------------------以下为非接触式存储卡API------------------------------------------*/
/*
函数声明    int PiccMemActive( unsigned short pi_usDelayTimes, unsigned char* po_pbysCardType, unsigned char* po_pbysUID );
功能描述    非接触式存储卡激活。
参数含义    pi_usDelayTimes：输入参数，等待卡进入感应区时间（单位：毫秒），
                             0 无需等待，无卡直接返回；
                             0xffff 一直等待。
            po_pbysCardType：输出参数，卡类别，1字节，
                             0AH  A卡;  
                             0BH  B卡。
            po_pbysUID：输出参数，卡UID，4字节。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemActive( unsigned short pi_usDelayTimes, unsigned char* po_pbysCardType, unsigned char* po_pbysUID );


/*
函数声明    int PiccMemActiveHex( unsigned short pi_usDelayTimes, unsigned char* po_pbysCardType, unsigned char* po_pbysUID );
功能描述    非接触式存储卡激活。
参数含义    pi_usDelayTimes：输入参数，等待卡进入感应区时间（单位：毫秒），
                             0 无需等待，无卡直接返回；
                             0xffff 一直等待。
            po_pbysCardType：输出参数，卡类别，1字节，
                             'A'  TYPE A卡;
                             'B'  TYPE B卡。
            po_pbysUID：输出参数，卡UID，8字节拆分后的UID，如0xAA 拆成 "AA"。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemActiveHex( unsigned short pi_usDelayTimes, unsigned char* po_pbysCardType, unsigned char* po_pbysUID );


/*
函数声明    int PiccMemAuthSector( unsigned char pi_bySectorNo, unsigned char pi_byKeyType, unsigned char* pi_bysKey );
功能描述    非接触式存储卡认证扇区。
参数含义    pi_bySectorNo：输入参数，扇区号。
            pi_byKeyType：输入参数，密钥类型，
                          0x60 A密钥；
                          0x61 B密钥；
                          0x40 加密后的A密钥；
                          0x41 加密后的B密钥。
            pi_pbysKey：输入参数，密钥，非加密模式时为6字节，加密模式为8字节。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemAuthSector( unsigned char pi_bySectorNo, unsigned char pi_byKeyType, unsigned char* pi_pbysKey );


/*
函数声明    int PiccMemAuthSectorHex( unsigned char pi_bySectorNo, unsigned char pi_byKeyType, unsigned char* pi_bysKey );
功能描述    非接触式存储卡认证扇区。
参数含义    pi_bySectorNo：输入参数，扇区号。
            pi_byKeyType：输入参数，密钥类型，
                          'A' A密钥；
                          'B' B密钥；
                          'a' 加密后的A密钥；
                          'b' 加密后的B密钥。
            pi_pbysKey：输入参数，密钥，非加密模式时为12字节拆分后的密钥, 加密模式时为16字节拆分后的密钥。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemAuthSectorHex( unsigned char pi_bySectorNo, unsigned char pi_byKeyType, unsigned char* pi_pbysKey );
                

/*
函数声明    int PiccMemReadBlock( unsigned char pi_byBlockNo, unsigned char* po_pbysBlockData );
功能描述    非接触式存储卡读块。
参数含义    pi_byBlockNo：输入参数，块号。
            po_pbysBlockData：输出参数，数据，16字节。
返回值        0 成功　-1失败 >0错误号
*/
int __stdcall PiccMemReadBlock( unsigned char pi_byBlockNo, unsigned char* po_pbysBlockData );
                                        

/*
函数声明    int PiccMemReadBlockHex( unsigned char pi_byBlockNo, unsigned char* po_pbysBlockData );
功能描述    非接触式存储卡读块。
参数含义    pi_byBlockNo：输入参数，块号 从0开始。
            po_pbysBlockData：输出参数，数据，32字节拆分后的块数据。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemReadBlockHex( unsigned char pi_byBlockNo, unsigned char* po_pbysBlockData );


/*
函数声明    int PiccMemWriteBlock( unsigned char pi_byBlockNo, unsigned char* pi_pbysBlockData );
功能描述    非接触式存储卡写块。
参数含义    pi_byBlockNo：输入参数，块号。
            pi_pbysBlockData：输入参数，数据，16字节。
返回值        0 成功　-1失败 >0错误号
*/
int __stdcall PiccMemWriteBlock( unsigned char pi_byBlockNo, unsigned char* pi_pbysBlockData );


/*
函数声明    int PiccMemWriteBlockHex( unsigned char pi_byBlockNo, unsigned char* pi_pbysBlockData );
功能描述    非接触式存储卡写块。
参数含义    pi_byBlockNo：输入参数，块号。
            pi_pbysBlockData：输入参数，数据，32字节拆分后的块数据。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemWriteBlockHex( unsigned char pi_byBlockNo, unsigned char* pi_pbysBlockData );


/*
函数声明    int PiccMemReadValue( unsigned char pi_byBlockNo, unsigned char* po_pbysValue );
功能描述    非接触式存储卡读值块。
参数含义    pi_byBlockNo：输入参数，块号。
            po_pbysValue：输出参数，数据，4字节。
返回值        0 成功　-1失败 >0错误号
*/
int __stdcall PiccMemReadValue( unsigned char pi_byBlockNo, unsigned char* po_pbysValue );


/*
函数声明    int PiccMemReadValueInt( unsigned char pi_byBlockNo, unsigned long* po_pulValue );
功能描述    非接触式存储卡读值块。
参数含义    pi_byBlockNo：输入参数，块号。
            po_pulValue：输出参数，值，无符号整型。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemReadValueInt( unsigned char pi_byBlockNo, unsigned long* po_pulValue );


/*
函数声明    int PiccMemWriteValue( unsigned char pi_byBlockNo, unsigned char* pi_pbysValue);
功能描述    非接触式存储卡写块值。
参数含义    pi_byBlockNo：输入参数，块号。
            po_pbysValue：输入参数，数据，4字节。
返回值        0 成功　-1失败 >0错误号
*/
int __stdcall PiccMemWriteValue( unsigned char pi_byBlockNo, unsigned char* pi_pbysValue);


/*
函数声明    int PiccMemWriteValueInt( unsigned char pi_byBlockNo, unsigned long* pi_pulValue );
功能描述    非接触式存储卡写值块。
参数含义    pi_byBlockNo：输入参数，块号。
            pi_pulValue：输入参数，值，无符号整型。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemWriteValueInt( unsigned char pi_byBlockNo, unsigned long* pi_pulValue );


/*
函数声明    int PiccMemIncValue( unsigned char pi_byBlockNo, unsigned char* pi_pbysValue );
功能描述    非接触式存储卡加值。
参数含义    pi_byBlockNo：输入参数，块号。
            pi_pbysValue：输入参数，数据，4字节。
返回值        0 成功　-1失败 >0错误号
*/
int __stdcall PiccMemIncValue( unsigned char pi_byBlockNo, unsigned char* pi_pbysValue );


/*
函数声明    int PiccMemIncValueInt( unsigned char pi_byBlockNo, unsigned long* pi_pulValue );
功能描述    非接触式存储卡加值。
参数含义    pi_byBlockNo：输入参数，块号。
            pi_pulValue：输入参数，值，无符号整型。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemIncValueInt( unsigned char pi_byBlockNo, unsigned long* pi_pulValue );


/*
函数声明    int PiccMemDecValue( unsigned char pi_byBlockNo, unsigned char* pi_pbysValue );
功能描述    非接触式存储卡减值。
参数含义    pi_byBlockNo：输入参数，块号。
            pi_pbysValue：输入参数，数据，4字节。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemDecValue( unsigned char pi_byBlockNo, unsigned char* pi_pbysValue );


/*
函数声明    int PiccMemDecValueInt( unsigned char pi_byBlockNo, unsigned long* pi_pulValue );
功能描述    非接触式存储卡减值。
参数含义    pi_byBlockNo：输入参数，块号。
            pi_pulValue：输入参数，值，无符号整型。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemDecValueInt( unsigned char pi_byBlockNo, unsigned long* pi_pulValue );


/*
函数声明    int PiccMemHalt(void)
功能描述    非接触式存储卡停止激活。
参数含义    输入参数 ：无。
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccMemHalt(void);


/*
函数声明    int PiccGetTagType( unsigned char* po_pbysTagType );
功能描述    获取非接触式卡卡片类型代码。
参数含义    po_pbysTagType：输出参数，卡片类型代码，2字节，其数值可参考如下(16进制表示)，
                            pucTagType[0]   pucTagType[1]    卡类型
                            04                00            Mifare_One(S50)
                            02                00            Mifare_One(S70)
                            44                00            Mifare_UltraLight
                            08                00            Mifare_Pro
                            04                03            Mifare_ProX
                            44                03            Mifare_DESFire
返回值        0 成功　-1通讯失败 >0错误号
*/
int __stdcall PiccGetTagType( unsigned char* po_pbysTagType );


/*--------------------------------------以下为二代证端口类API------------------------------------------*/
/*
函数声明    int SDT_GetCOMBaud( int iPort, unsigned int* puiBaudRate );
功能描述    查看SAM_V当前波特率(该函数只用于SAM_V采用RS232串口的情形，如果采用USB接口则不支持该API)。
参数含义    iPort：输入参数,整数，表示端口号。此处端口号必须为1-16，表示串口。
            puiBaudRate：输出参数，无符号整数指针，指向普通串口当前波特率, 默认情况下为115200。
返回值      0x90 成功
            0x01 端口打开失败/端口号不合法
            0x05 无法获得该SAM_V的波特率，该SAM_V串口不可用。
*/
int __stdcall SDT_GetCOMBaud( int iPort, unsigned int* puiBaudRate );


/*
函数声明    int SDT_SetCOMBaud( int iPort, unsigned int uiCurrBaud, unsigned int uiSetBaud );
功能描述    设置SAM_V的串口的波特率(该函数只用于SAM_V采用RS232串口的情形，如果采用USB接口则不支持该API)，
            设置成功后，在该SAM_V和主机注册表中都记录设置后的波特率，保证在SAM_V重新启动和该套API被重新调
            用时采用设置后的波特率。该函数调用成功后，需要延时5毫秒，然后才能继续与SAM_V通信。
参数含义    iPort：输入参数,整数，表示端口号。此处端口号必须为1-16，表示串口。
            uiCurrBaud：输入参数，无符号整数，调用该API前已设置的业务终端与SAM_V通信的波特率(SAM_V出厂时默认,
                        业务终端与SAM_V通信的波特率为115200).业务终端以该波特率与SAM_V通信,发出设置SAM_V新波
                        特率的命令.。uiCurrBaud只能为下列数值之一：115200，57600，38400，19200，9600.
                        如果uiCurrBaud数值不是这些值之一，函数返回0x21;如果已设置的波特率与uiCurrBaud不一致, 
                        则函数返回0x02,表示不能设置,调用API不成功。
            uiSetBaud：输入参数，无符号整数，将要设置的SAM_V与业务终端通信波特率。uiSetBaud只能取下列值之一：
                        115200，57600，38400，19200，9600，如果输入uiSetBaud参数不是这些数值之一,，函数返回0x21,
                        设置不成功,保持原来的波特率不变。
返回值      0x90 成功
            0x01 端口打开失败/端口号不合法。
            0x02 超时，设置不成功。
            0x21 uiCurrBaud 、uiSetBaud输入参数数值错误.。
*/
int __stdcall SDT_SetCOMBaud( int iPort, unsigned int uiCurrBaud, unsigned int uiSetBaud );


/*
函数声明    int SDT_OpenPort( int iPort );
功能描述    打开串口/USB 口。
参数含义    iPort：输入参数，整数，表示端口号。
                   串口和 USB 都只支持 16 个，分别为 1〜16(十进制) 为串口，1001〜1016(十进制)为 USB 口；
                   串口 1〜16 例如： 1：串口 1(COM1) 2：串口 2(COM2)；
                   USB口 1001〜1016 例如： 1001：USB1 1002：USB2。
返回值      0x90 打开端口成功； 
            0x01 打开端口失败/端口号不合法。 
*/
int __stdcall SDT_OpenPort( int iPort );


/*
函数声明    int SDT_ClosePort( int iPort )
功能描述    关闭串口/USB 口。
参数含义    iPort：输入参数，整数，表示端口号。参见 SDT_OpenPort。
返回值      0x90 打开端口成功；
            0x01 打开端口失败/端口号不合法。 
*/
int __stdcall SDT_ClosePort( int iPort );


/*--------------------------------------以下为二代证SAM类AP------------------------------------------*/
/*
函数声明    int SDT_ResetSAM( int iPort, int iIfOpen );
功能描述    对SAM_A复位。
参数含义    iPort：输入参数，整数，表示端口号。参见 SDT_OpenPort。
            iIfOpen：输入参数，整数，
                     0 表示不在该函数内部打开和关闭串口，此时应确保之前调用了 SDT_OpenPort 打开端口，并且应在不需要与端口通信时，调用 SDT_ClosePort 关闭端口；
                     非 0 表示在 API 函数内部包含了打开端口和关闭端口函数，之前不 需要调用 SDT_OpenPort，也不用再调用 SDT_ClosePort。 
返回值      0x90 成功；
            其它 失败(具体含义参见二代证返回错误定义)。
*/
int __stdcall SDT_ResetSAM( int iPort, int iIfOpen );


/*
函数声明    int SDT_GetSAMStatus( int iPort ,int iIfOpen );
功能描述    对 SAM_A 进行状态检测。
参数含义    iPort：输入参数，整数，表示端口号。参见 SDT_OpenPort。
            iIfOpen：输入参数，整数，参见SDT_ResetSAM。
返回值      0x90 SAM_A正常；
            0x60 自检失败，不能接收命令；
            其它 失败(具体含义参见二代证返回错误定义)。
*/
int __stdcall SDT_GetSAMStatus( int iPort ,int iIfOpen );


/*
函数声明    int SDT_GetSAMID( int iPort, unsigned char* pucSAMID, int iIfOpen );
功能描述    读取SAM_A的编号，输出为十六进制数值。
参数含义    iPort：输入参数，整数，表示端口号。参见 SDT_OpenPort。
            pucSAMID：输出参数，无符号字符串指针，SAM_A编号，16字节。该指针指向的存储空间由调用者分配。
            iIfOpen：输入参数，整数，参见SDT_ResetSAM。
返回值      0x90 成功；
            其它 失败(具体含义参见二代证返回错误定义)。
*/
int __stdcall SDT_GetSAMID( int iPort, unsigned char* pucSAMID, int iIfOpen );


/*
函数声明    int SDT_GetSAMIDToStr( int iPort, char* pcSAMID ,int iIfOpen );
功能描述    读取SAM_A的编号，输出为字符串。
参数含义    iPort：输入参数，整数，表示端口号。参见 SDT_OpenPort。
            pcSAMID：输出参数，字符串指针，SAM_A编号。该指针指向的存储空间由调用者分配，不得小于40 字节。
            iIfOpen：输入参数，整数，参见SDT_ResetSAM。
返回值      0x90 成功；
            其它 失败(具体含义参见二代证返回错误定义)。
*/
int __stdcall SDT_GetSAMIDToStr( int iPort, char* pcSAMID ,int iIfOpen );


/*--------------------------------------以下为二代证卡类API------------------------------------------*/
/*
函数声明    int SDT_StartFindIDCard( int iPort, unsigned char* pucManaInfo ,int iIfOpen );
功能描述    寻找居民身份证。
参数含义    iPort：输入参数，整数，表示端口号。参见 SDT_OpenPort。
            pucManaInfo：输出参数，无符号字符型指针，4个字节0x00。该指针指向的存储空间由调用者分配。
            iIfOpen: 输入参数，整数，参见SDT_ResetSAM。
返回值      0x9f 找卡成功；
            0x80 找卡失败。
*/
int __stdcall SDT_StartFindIDCard( int iPort, unsigned char* pucManaInfo ,int iIfOpen );


/*
函数声明    int SDT_SelectIDCard( int iPort ,unsigned char* pucManaMsg, int iIfOpen );
功能描述    选卡。
参数含义    iPort：输入参数，整数，表示端口号。参见 SDT_OpenPort。
            pucManaMsg：输出参数，无符号字符型指针。该指针指向的存储空间由调用者分配，不小于8字节。
            iIfOpen: 输入参数，整数，参见SDT_ResetSAM。
返回值      0x90 选卡成功；
            0x81 选卡失败。
*/
int __stdcall SDT_SelectIDCard( int iPort ,unsigned char* pucManaMsg, int iIfOpen );


/*
函数声明    int __stdcall SDT_ReadBaseMsg(  int iPort ,
                                            unsigned char* pucCHMsg ,
                                            unsigned int* puiCHMsgLen, 
                                            unsigned char* pucPHMsg ,
                                            unsigned int* puiPHMsgLen, 
                                            int iIfOpen );
功能描述    读取居民身份证机读文字信息和相片信息。
参数含义    iPort：          输入参数，整数，表示端口号。参见 SDT_OpenPort。
            pucCHMsg：       输出参数，无符号字符型指针，指向读到的文字信息,其长度由puiCHMsgLen参数输出。该指针指向的存储空间由调用者分配，不得小于256字节。
            puiCHMsgLen：    输出参数，无符号整型数指针，指向读到的文字信息长度，最长256字节。
            pucPHMsg：       输出参数，无符号字符型指针，指向读到的相片信息，其长度由puiPHMsgLen参数输出。该指针指向的存储空间由调用者分配，不得小于1024字节。 
            puiPHMsgLen：    输出参数，无符号整型数指针，指向读到的相片信息长度，最长1024字节。 
            iIfOpen:         输入参数，整数，参见SDT_ResetSAM。
返回值      0x90 读机读文字信息和相片信息成功；
            其它 读机读文字信息和相片信息失败(具体含义参见二代证返回错误定义)。
*/
int __stdcall SDT_ReadBaseMsg(  int iPort ,
                                unsigned char* pucCHMsg ,
                                unsigned int* puiCHMsgLen, 
                                unsigned char* pucPHMsg ,
                                unsigned int* puiPHMsgLen, 
                                int iIfOpen );


/*
函数声明    int __stdcall SDT_ReadBaseFPMsg(int iPort ,
                                            unsigned char* pucCHMsg ,
                                            unsigned int* puiCHMsgLen ,
                                            unsigned char* pucPHMsg ,
                                            unsigned int* puiPHMsgLen, 
                                            unsigned char* pucFPMsg, 
                                            unsigned int* puiFMsgLen, 
                                            int iIfOpen );
功能描述    读取居民身份证机读文字信息、相片信息和指纹信息。
            注意：该接口只能用于支持读取指纹信息的 SAM_A。 
参数含义    iPort：          输入参数，整数，表示端口号。参见 SDT_OpenPort。
            pucCHMsg：       输出参数，无符号字符型指针，指向读到的文字信息,其长度由puiCHMsgLen参数输出。该指针指向的存储空间由调用者分配，不得小于256字节。
            puiCHMsgLen：    输出参数，无符号整型数指针，指向读到的文字信息长度，最长256字节。
            pucPHMsg：       输出参数，无符号字符型指针，指向读到的相片信息，其长度由puiPHMsgLen参数输出。该指针指向的存储空间由调用者分配，不得小于1024字节。 
            puiPHMsgLen：    输出参数，无符号整型数指针，指向读到的相片信息长度，最长1024字节。
            pucFPMsg：       输出参数，无符号字符型指针，指向读到的指纹信息,其长度由puiFPMsgLen参数输出。该指针指向的存储空间由调用者分配，不得小于1024字节。
            puiFPMsgLen：    输出参数，无符号整型数指针，指向读到的指纹信息长度，最长1024字节。
            iIfOpen:         输入参数，整数，参见SDT_ResetSAM。
返回值      0x90 读机读文字信息和相片信息成功；
            其它 读机读文字信息和相片信息失败(具体含义参见二代证返回错误定义)。
*/
int __stdcall SDT_ReadBaseFPMsg(int iPort ,
                                unsigned char* pucCHMsg ,
                                unsigned int* puiCHMsgLen ,
                                unsigned char* pucPHMsg ,
                                unsigned int* puiPHMsgLen, 
                                unsigned char* pucFPMsg, 
                                unsigned int* puiFMsgLen, 
                                int iIfOpen );


/*
函数声明    int SDT_ReadNewAppMsg( int iPort ,unsigned char* pucAppMsg, unsigned int* puiAppMsgLen, int iIfOpen );
功能描述    读取追加地址信息。
参数含义    iPort：          输入参数，整数，表示端口号。参见 SDT_OpenPort。
            pucAppMsg：      输出参数，无符号字符串，指向读到的追加地址信息，其长度由puiAppMsgLen参数输出。该指针指向的存储空间由调用者分配，不得小于70字节。
            puiAppMsgLen：   输出参数，指向整数的指针，指向读到的追加地址信息长度，最长70字节。
            iIfOpen:         输入参数，整数，参见SDT_ResetSAM。
返回值      0x90 读取追加地址信息成功；
            0x91 居民身份证中无追加地址信息；
            其它 读取追加地址信息失败(具体含义参见二代证返回错误定义)。
*/
int __stdcall SDT_ReadNewAppMsg( int iPort ,unsigned char* pucAppMsg, unsigned int* puiAppMsgLen, int iIfOpen );

};
#endif//_HXGC_DEVICE_API_J10_H_