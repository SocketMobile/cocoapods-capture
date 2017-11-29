/**
    @file SktCaptureProperty.h
    @brief define the properties used in Capture

    @date 1/29/17
    @copyright © 2017 Socket Mobile, Inc.

*/

#ifndef SktCaptureProperty_h
#define SktCaptureProperty_h

#import "SktCapturePropertyIds.h"

/**
 @brief device type class
 */
typedef NS_ENUM (NSInteger, SKTCaptureDeviceClass) {
    SKTCaptureDeviceTypeClassDevice, /** the device belongs to the device class */
    SKTCaptureDeviceTypeClassDeviceManager /** the device belongs to the device manager class */
};

/**
 @brief Capture Device Interface type

 */
typedef NS_ENUM (NSInteger, SKTCaptureDeviceInterfaceType) {
    SKTCaptureDeviceInterfaceTypeNone = 0, /** interface not specified */
    SKTCaptureDeviceInterfaceTypeSD = 1, /** interface Secure Digital */
    SKTCaptureDeviceInterfaceTypeCF = 2, /** interface Compact Flash */
    SKTCaptureDeviceInterfaceTypeBluetooth = 3, /** interface Bluetooth */
    SKTCaptureDeviceInterfaceTypeSerial = 4, /** interface Serial */
    SKTCaptureDeviceInterfaceTypeBle = 5 /** interface BLE */
};

/**

 @brief Capture Device product type

 */
typedef NS_ENUM (NSInteger, SKTCaptureDeviceProductId) {
    SKTCaptureDeviceProductIdNone, /** no product type speficied */
    SKTCaptureDeviceProductId7Series, /** product of the 7 Series */
    SKTCaptureDeviceProductId7xSeries, /** product of the 7x Series */
    SKTCaptureDeviceProductId9Series, /** product of the 9 Series */
    SKTCaptureDeviceProductId7xiSeries, /** product of the 7xi Series */
    SKTCaptureDeviceProductIdSoftScan, /** product of SoftScan type */
    SKTCaptureDeviceProductId8ciSeries, /** product of 8ci Series */
    SKTCaptureDeviceProductId8qiSeries, /** product of 8qi Series */
    SKTCaptureDeviceProductIdD700Series, /** product of D700 Series */
    SKTCaptureDeviceProductIdD730Series, /** product of D730 Series */
    SKTCaptureDeviceProductIdD750Series, /** product of the D750 Series */
    SKTCaptureDeviceProductIdD600Series, /** product of the D600 Series */
    SKTCaptureDeviceProductIdUnknown /** product unknown */
};

/**
 @brief Identifier for the Device Managers
 */
typedef NS_ENUM (NSInteger, SKTCaptureDeviceManagerId) {
    SKTCaptureDeviceManagerIdNone,/** no device manager - regular device */
    SKTCaptureDeviceManagerIdBle, /** BLE device manager */
    SKTCaptureDeviceManagerIdUnknown /** unknown device manager, does Capture need to be updated? */
};

/**

 @brief the device type is a combination of product type and interface

 */
typedef NS_ENUM (NSInteger, SKTCaptureDeviceType) {
    SKTCaptureDeviceTypeNone =
    SKTCaptureDeviceInterfaceTypeNone<<16 | SKTCaptureDeviceProductIdNone, /** unknown device type */
    SKTCaptureDeviceTypeScanner7 =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductId7Series, /** Scanner 7 device type */
    SKTCaptureDeviceTypeScanner7x =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductId7xSeries, /** Scanner 7x device type */
    SKTCaptureDeviceTypeScanner7xi =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductId7xiSeries, /** Scanner 7xi device type */
    SKTCaptureDeviceTypeScanner9 =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductId9Series, /** Scanner 9 device type */
    SKTCaptureDeviceTypeSoftScan =
    SKTCaptureDeviceInterfaceTypeNone<<16 | SKTCaptureDeviceProductIdSoftScan, /** SoftScan device type */
    SKTCaptureDeviceTypeScanner8ci =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductId8ciSeries, /** Scanner 8ci device type */
    SKTCaptureDeviceTypeScanner8qi =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductId8qiSeries, /** Scanner 8qi device type */
    SKTCaptureDeviceTypeScannerD700 =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductIdD700Series, /** Scanner D700 device type */
    SKTCaptureDeviceTypeScannerD730 =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductIdD730Series, /** Scanner D730 device type */
    SKTCaptureDeviceTypeScannerD750 =
    SKTCaptureDeviceInterfaceTypeBluetooth<<16 | SKTCaptureDeviceProductIdD750Series, /** Scanner D750 device type */
    SKTCaptureDeviceTypeScannerD600 = SKTCaptureDeviceTypeClassDevice<<24 |
    SKTCaptureDeviceInterfaceTypeBle<<16 | SKTCaptureDeviceProductIdD600Series,/** Scanner D600 device type */

    // device Manager
    SKTCaptureDeviceManagerTypeBle = SKTCaptureDeviceTypeClassDeviceManager<<24 |
    SKTCaptureDeviceInterfaceTypeBle<<16 | SKTCaptureDeviceManagerIdBle, /** BLE Device Manager type */

};

/**

 @brief Data Confirmation mode defines how the decoded data should be confirmed.

 */
typedef NS_ENUM (NSInteger, SKTCaptureDataConfirmation)
{
    SKTCaptureDataConfirmationModeOff, /** use the device configuration (Local Confirmation or App) */
    SKTCaptureDataConfirmationModeDevice, /** the device confirms the decoded data locally */
    SKTCaptureDataConfirmationModeCapture, /** Capture confirms the decoded data as it receives them and there is one app */
    SKTCaptureDataConfirmationModeApp /** the Application confirms the decoded data as it receives them */
};

/**

 @brief Device Data Acknowledgment mode
 */
typedef NS_ENUM (NSInteger, SKTCaptureDeviceDataAcknowledgment)
{
    SKTCaptureDeviceDataAcknowledgmentOff, /** the device won't locally acknowledge decoded data */
    SKTCaptureDeviceDataAcknowledgmentOn, /** the device will locally acknowledge decoded data */
};

/**

 @brief define the device security mode
 */
typedef NS_ENUM (NSInteger, SKTCaptureSecurityMode )
{
    SKTCaptureSecurityModeNone, /** no security */
    SKTCaptureSecurityModeAuthentication, /** authentication only */
    SKTCaptureSecurityModeAuthenticationEncryption, /** authentication and encryption */
};

/**

 @brief Trigger parameter

 */
typedef NS_ENUM (NSInteger, SKTCaptureTrigger )
{
    SKTCaptureTriggerStart=1, /** start a scan */
    SKTCaptureTriggerStop, /** stop a scan */
    SKTCaptureTriggerEnable, /** enable the trigger */
    SKTCaptureTriggerDisable, /** disable the trigger */
    SKTCaptureTriggerContinuousScan, /** start a scan in continuous mode (SoftScan scanner only, ESKT_NOTSUPPORTED returned when used with other scanner) */
};

/**

 @brief Delete Pairing Parameter

 */
typedef NS_ENUM (NSInteger, SKTCaptureDeletePairing )
{
    SKTCaptureDeletePairingCurrent=0, /** delete only the current pairing information */
    SKTCaptureDeletePairingAll=1, /** delete all the pairing information */
};

/**

 @brief action when the device successful decode data

 */
typedef NS_ENUM (NSInteger, SKTCaptureSoundActionType)
{
    SKTCaptureSoundActionTypeGoodScan, /** good read from the host */
    SKTCaptureSoundActionTypeGoodScanLocal, /** good read from the device */
    SKTCaptureSoundActionTypeBadScan, /** bad read from the host */
    SKTCaptureSoundActionTypeBadScanLocal, /** bad read from the device */
};

/**

 @brief sound configuration frequency

 */
typedef NS_ENUM (NSInteger, SKTCaptureSoundFrequency)
{
    SKTCaptureSoundFrequencyNone=0, /** no frequency sound */
    SKTCaptureSoundFrequencyLow, /** low frequency sound */
    SKTCaptureSoundFrequencyMedium, /** medium frequency sound */
    SKTCaptureSoundFrequencyHigh, /** high frequency sound */
    SKTCaptureSoundFrequencyLast /** not a frequency sound value */
};

/**

 @brief Rumble configuration for a specific action Type

 */
typedef NS_ENUM (NSInteger, SKTCaptureRumbleActionType)
{
    SKTCaptureRumbleActionTypeGoodScan, /** Vibrate when the host is ack'ing positively the decoded data */
    SKTCaptureRumbleActionTypeGoodScanLocal, /** Vibrate when the device is ack'ing positively the decoded data */
    SKTCaptureRumbleActionTypeBadScan, /** Vibrate when the host is ack'ing negatively the decoded data */
    SKTCaptureRumbleActionTypeBadScanLocal /** Vibrate when the device ack'ing negatively the decoded data */
};


/**


 @brief configure the local decode action when the device has a good read

 */
typedef NS_OPTIONS (NSInteger, SKTCaptureLocalDecodeAction)
{
    SKTCaptureLocalDecodeActionNone=0, /** no decode action when the device reads correctly */
    SKTCaptureLocalDecodeActionBeep=1, /** the device beeps when it reads correctly */
    SKTCaptureLocalDecodeActionFlash=2, /** the device LED flashes when it reads correctly */
    SKTCaptureLocalDecodeActionRumble=4 /** the device vibrates when it reads correctly */
};

/**

 @brief Device LED configuration when confirming a read

 */
typedef NS_ENUM (NSInteger, SKTCaptureDataConfirmationLed)
{
    SKTCaptureDataConfirmationLedNone=0, /** Device LED do nothing when confirming a read */
    SKTCaptureDataConfirmationLedGreen=1, /** Device LED flashes in green when confirming a read */
    SKTCaptureDataConfirmationLedRed=2 /** Device LED flashes in red when confirming a read */
};

/**

 @brief Device beep configuration when confirming a read

 */
typedef NS_ENUM (NSInteger, SKTCaptureDataConfirmationBeep)
{
    SKTCaptureDataConfirmationBeepNone=0, /** Device makes no beep when confirming a read */
    SKTCaptureDataConfirmationBeepGood=1, /** Device makes a good beep when confirming a read */
    SKTCaptureDataConfirmationBeepBad=2 /** Device makes a bad beep when confirming a read */
};

/**


 @brief Device rumble configuration when confirming a read

 */
typedef NS_ENUM (NSInteger, SKTCaptureDataConfirmationRumble)
{
    SKTCaptureDataConfirmationRumbleNone=0, /** no rumble when confirming a read */
    SKTCaptureDataConfirmationRumbleGood=1, /** good rumble when confirming a read */
    SKTCaptureDataConfirmationRumbleBad=2 /** bad rumble when confirming a read */
};

/**


 @brief SoftScan flash setting

 */
typedef NS_ENUM (NSInteger, SKTCaptureFlash)
{
    SKTCaptureFlashOff=0, /**  turn the flash off */
    SKTCaptureFlashOn=1 /** turn the flash on */
};

/**


 @brief status of the SoftScan scanner. Sofscan is a barcode scanner using the
 device camera.

 */
typedef NS_ENUM (NSInteger, SKTCaptureSoftScan)
{
    SKTCaptureSoftScanEnable=0, /** the SoftScan feature is enabled */
    SKTCaptureSoftScanDisable=1, /** the SoftScan feature is disabled */
    SKTCaptureSoftScanNotSupported=2, /** make the SoftScan feature not supported (Set Property only) */
    SKTCaptureSoftScanSupported=3 /** make the SoftScan feature supported (Set property only) */
};

/**
    KVC key for the SoftScan Overlay definition. The context should be
 the application UIViewController from which the SoftScan viewfinder should be
 attached.
 */
extern NSString* _Nonnull SKTCaptureSoftScanContext;

/**
 KVC key for the Layout ID. This is not used in iOS, it is ignored if set.
 */
extern NSString* _Nonnull SKTCaptureSoftScanLayoutId;

/**
 KVC key for the viewfinder ID. This is not used in iOS, it is ignored if set.
 */
extern NSString* _Nonnull SKTCaptureSoftScanViewFinderId;
/**
 KVC key for the SoftScan Flash Button ID. This is not used in iOS, it is ignored if set.
 */
extern NSString* _Nonnull SKTCaptureSoftScanFlashButtonId;

/**
 KVC text to display on the Cancel button in the SoftScan overlay
 if this key value is missing the English version is displayed by default
 */
extern NSString* _Nonnull SKTCaptureSoftScanCancelButton;
/**
 KVC for if the dictionary for SoftScan overlay doesn't have this
 key, the flash button won't be displayed in the overlay
 */
extern NSString* _Nonnull SKTCaptureSoftScanFlashButton;// coma-separated text: Flash,ON,OFF
/**
 KVC key for the text that gives some direction to the user on how to scan with SoftScan.
 */
extern NSString* _Nonnull SKTCaptureSoftScanDirectionText;
/**
 KVC key for the Background Color
 */
extern NSString* _Nonnull SKTCaptureSoftScanBackgroundColor;//"rgb() or rgba()
/**
 KVC key  for the SoftScan viewfinder text color
 */
extern NSString* _Nonnull SKTCaptureSoftScanTextColor;//"rgb() or rgba()
/**
 KVC key for selecting which camera (front or back) SoftScan should use
 */
extern NSString* _Nonnull SKTCaptureSoftScanCamera; // "front" "back"

/**
 @brief identify the device button for which the button event is received
 */
typedef NS_OPTIONS(NSInteger, SKTCaptureButtonsState)
{
    SKTCaptureButtonsStateLeft=0x01, /** the left button has its state changed */
    SKTCaptureButtonsStateRight=0x02, /** the right button has its state changed */
    SKTCaptureButtonsStateMiddle=0x04, /** the middle button has its state changed */
    SKTCaptureButtonsStatePower=0x08, /** the power button has its state changed */
    SKTCaptureButtonsStateRingDetach=0x10 /** the ring detach state has changed (Series 9 only) */
};


/**
 @brief define the power state
 */
typedef NS_ENUM(NSInteger, SKTCapturePowerState)
{
    SKTCapturePowerStateUnknown=0x00, /** the power state is unknown */
    SKTCapturePowerStateOnBattery=0x01, /** the power comes from battery */
    SKTCapturePowerStateOnCradle=0x02, /** the power comes from cradle */
    SKTCapturePowerStateOnAc=0x04 /** the power comes from AC */
};

/**

 @brief define the type of profile

 */
typedef NS_ENUM(NSInteger, SKTCaptureProfileSelect)
{
    SKTCaptureProfileSelectNone=0, /** the profile has no type */
    SKTCaptureProfileSelectSpp=1, /** the profile is Serial Port Profile */
    SKTCaptureProfileSelectHid=2 /** the profile is Keyboard emulation HID */
};

/**

 @brief define the role of the device

*/
typedef NS_ENUM(NSInteger, SKTCaptureProfileConfig)
{
    SKTCaptureProfileConfigNone=0, /** do nothing when the profile is active */
    SKTCaptureProfileConfigAcceptor=1, /** accepts incoming connection when the profile is active */
    SKTCaptureProfileConfigInitiator=2 /** initiate a connection when the profile is active */
};

/**

 @brief parameter for the disconnect property (set only)

 */
typedef NS_ENUM(NSInteger, SKTCaptureDisconnect)
{
    SKTCaptureDisconnectStartProfile=0, /** disconnect and then start the selected profile */
    SKTCaptureDisconnectDisableRadio=1, /** disconnect and disable the radio (low power) */
};

/**

 @brief notification configuration. This configuration is a bitmask

 */
typedef NS_OPTIONS(NSInteger, SKTCaptureNotifications)
{
    SKTCaptureNotificationsNone=0, /** disable all notifications */
    SKTCaptureNotificationsScanButtonPress=1<<0, /** enable scan button press notifications */
    SKTCaptureNotificationsScanButtonRelease=1<<1, /** enable scan button release notifications */
    SKTCaptureNotificationsPowerButtonPress=1<<2, /** enable power button release notifications */
    SKTCaptureNotificationsPowerButtonRelease=1<<3, /** enable power button release notifications */
    SKTCaptureNotificationsPowerState=1<<4, /** enable power state change notifications */
    SKTCaptureNotificationsBatteryLevelChange=1<<5 /** enable battery level change notifications */
};

/**

 @brief start up role when in SPP configuration mode

 */
typedef NS_ENUM(NSInteger, SKTCaptureStartUpRole)
{
    SKTCaptureStartUpRoleSPPAcceptor=0, /** the SPP Role will always be Acceptor */
    SKTCaptureStartUpRoleSPPLastRole=1 /** the SPP Role will always be what was the last SPP Role config */
};

/**

 @brief connect beep configuration

 */
typedef NS_ENUM(NSInteger, SKTCaptureConnectBeepConfig)
{
    SKTCaptureConnectBeepConfigNoBeep=0, /** don't beep when a connection is established */
    SKTCaptureConnectBeepConfigBeep=1 /** Beep when a connection is established */
};

/**

 @brief define the data format

 */
typedef NS_ENUM(NSInteger, SKTCaptureDataFormat)
{
    SKTCaptureDataFormatRaw=0, /** data format without protocol fields */
    SKTCaptureDataFormatPacket=1 /** data format respecting the protocol format */
};

/**

 @brief identify the timer for which the value are defined

 */
typedef NS_ENUM(NSInteger, SKTCaptureTimer)
{
    SKTCaptureTimerTriggerAutoLockTimeout=1, /** Trigger lock selected */
    SKTCaptureTimerPowerOffDisconnected=2, /** Disconnected state timeout */
    SKTCaptureTimerPowerOffConnected=4 /** Connected state timeout */
};

/**

 @brief gives the reason for the connection to occur

 */
typedef NS_ENUM(NSInteger, SKTCaptureConnectReason)
{
    SKTCaptureConnectReasonUnknown=0, /** unknown reason */
    SKTCaptureConnectReasonPowerOn=1, /** the device has connected because it powers on */
    SKTCaptureConnectReasonBarcode=2, /** the device has connected because it scans a connect barcode */
    SKTCaptureConnectReasonUserAction=3, /** the device has connected because the user press the power button or the trigger button */
    SKTCaptureConnectReasonHostChange=4, /** the device has connected because the host has changed */
    SKTCaptureConnectReasonRetry=5, /** the device has connected because it is back in range */
};

/**

 @brief stand configuration

 */
typedef NS_ENUM(NSInteger, SKTCaptureStandConfig) {
    SKTCaptureStandConfigMobileMode=0, /** the device is always in trigger mode */
    SKTCaptureStandConfigKioskMode=1, /** the device is always in presentation mode */
    SKTCaptureStandConfigDetectMode=2, /** the device is in presentation mode when resting on stand, trigger mode otherwise */
    SKTCaptureStandConfigAutoMode=3, /** the device stays in presentation mode until trigger is pressed, goes back in presentation when resting on stand */
};

/**

 @brief type of the property parameter

 */
typedef NS_ENUM(NSInteger, SKTCapturePropertyType) {
    SKTCapturePropertyTypeNone, /** the property does not have parameter */
    SKTCapturePropertyTypeNotApplicable, /** the parameter is not applicable for the property */
    SKTCapturePropertyTypeByte, /** the property has a byte as parameter */
    SKTCapturePropertyTypeUlong, /** the property has an unisgned long integer as parameter */
    SKTCapturePropertyTypeArray, /** the property has a byte array as parameter */
    SKTCapturePropertyTypeString, /** the property has a length variable string as parameter */
    SKTCapturePropertyTypeVersion, /** the property has a version structure as parameter */
    SKTCapturePropertyTypeDataSource, /** the property has a Data Source structure as parameter */
    SKTCapturePropertyTypeEnum, /** the property has an enumeration structure as parameter */
    SKTCapturePropertyTypeObject, /** the property has an object as parameter */
    SKTCapturePropertyTypeLastType, /** this is not a parameter property type but it gives the number of enums */
};

/**
 @class SKTCaptureProperty

 @brief define a Capture Property composed by a Property ID, a Property Type and
 an eventual property parameter of the specified type.

 */
@interface SKTCaptureProperty : NSObject

/**
 @brief get or set the property ID
 */
@property SKTCapturePropertyID ID;

/**
 @brief get or set the type of the property parameter
 */
@property SKTCapturePropertyType Type;

/**
 @brief property array of byte parameter
 */
@property (nullable, nonatomic, strong) NSData* ArrayValue;

/**
 @brief property string parameter
 */
@property (nullable, nonatomic, strong) NSString* StringValue;

/**
 @brief property byte value parameter
 */
@property int8_t ByteValue;

/**
 @brief property unsigned long integer parameter
 */
@property unsigned long ULongValue;

/**
 @brief property version parameter
 */
@property (nullable, nonatomic, strong) SKTCaptureVersion* Version;

/**
 @brief property data source parameter
 */
@property (nullable, nonatomic, strong) SKTCaptureDataSource* DataSource;

/**
 @brief property user context
 */
@property (nullable) void *Context;

/**
 @brief property pointer to object parameter
 */
@property (nullable, retain) NSObject *Object;

/**
 @brief initialize the property object
 */
-(instancetype _Nonnull ) init;

@end

#endif /* SktCaptureProperty_h */
