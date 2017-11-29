/**
    @file SktCaptureEvent.h
    @brief define the events received by Capture

    @copyright © 2017 Socket Mobile, Inc.


*/

#ifndef SktCaptureEvent_h
#define SktCaptureEvent_h

@class SKTCaptureEventData;

/**
 defines the events that can be received from Capture.

 */
typedef NS_ENUM(NSInteger, SKTCaptureEventID) {
 SKTCaptureEventIDNotInitialized, /** the event ID is not initialized */
 SKTCaptureEventIDDeviceArrival, /** event when a device has connected or is present */
 SKTCaptureEventIDDeviceRemoval, /** event when a device is no longer present */
 SKTCaptureEventIDTerminate, /** event when Capture is terminated */
 SKTCaptureEventIDError, /** event when Capture had an error */
 SKTCaptureEventIDDecodedData, /** event when Capture has some decoded data available */
 SKTCaptureEventIDPower, /** event when a device sends a power change notification */
 SKTCaptureEventIDButtons, /** event when the device button status has changed */
 SKTCaptureEventIDBatteryLevel, /** event when the attery Level has changed */
 SKTCaptureEventIDListenerStarted, /** event when the communication port listener has started */
 SKTCaptureEventIDDeviceOwnership, /** event when a device ownership has changed */
 SKTCaptureEventIDDeviceManagerArrival,// Device Manager Arrival (BLE)
    SKTCaptureEventIDDeviceManagerRemoval,// Device Manager Removal (BLE)
    SKTCaptureEventIDDeviceDiscovered,// Device Discovered (BLE)
    SKTCaptureEventIDDiscoveryEnd, // End of a Device Discovery (BLE)
    SKTCaptureEventIDLastID, /** -not an event- numeric value representing the number of events */
};

/**
    @class SKTCaptureEvent

    @brief define a Capture event, which has an ID, a data type and data.
 */
@interface SKTCaptureEvent : NSObject

/** @brief get or set the Capture event ID */
@property SKTCaptureEventID ID;

/** @brief get or set the Capture event data */
@property (nullable, nonatomic, strong) SKTCaptureEventData* Data;
@end

/**
 defines the Capture event data type.

 */
typedef NS_ENUM(NSInteger, SKTCaptureEventDataType) {
 SKTCaptureEventDataTypeNone, /** no data associated to the event. */
 SKTCaptureEventDataTypeByte, /** the data associated to the event is a byte. */
 SKTCaptureEventDataTypeUlong, /** the data associated to the event is a long integer */
 SKTCaptureEventDataTypeArray, /** the data associated to the event is an array. */
 SKTCaptureEventDataTypeString, /** the data associated to the event is a string. */
 SKTCaptureEventDataTypeDecodedData, /** the data associated to the event is a decoded data */
 SKTCaptureEventDataTypeDeviceInfo, /** the data associated to the event contains the device guid, type, and name */
 SKTCaptureEventDataTypeLastID, /** not an event type just a numeric value for the number of data types */
};

/**
 @class SKTCaptureDecodedData

 @brief define a Capture event Decoded Data, which has a Symbology ID, Symbology Name and decoded data.
 */
@interface SKTCaptureDecodedData : NSObject

/** @brief get the decoded data source ID */
@property SKTCaptureDataSourceID DataSourceID;

/** @brief get the data source name */
@property (nullable, nonatomic, strong) NSString* DataSourceName;

/** @brief get the decoded data*/
@property (nullable, nonatomic, strong) NSData* DecodedData;

/**

 @brief get the decoded data as string UTF8 encoded

 @remark there is no guaranty this property displays
        the decoded data if the data in the barcode
        are not UTF8 encoded.
 */
-( NSString* _Nullable) stringFromDecodedData;
@end

/**
 @class SKTCaptureDeviceInfo

 @brief contains the information about the device such as
        the device type, the device GUID
 */
@interface SKTCaptureDeviceInfo : NSObject

/**
 @brief Name of the device
 */
@property (retain, nonatomic) NSString* _Nullable Name;

/**
 @brief GUID of the device
 */
@property (retain, nonatomic) NSString* _Nullable Guid;

/**
 @brief Handle of the device
 */
@property SKTHandle _Nullable Handle;

/**
 @brief Device Type: (D750, S800 etc..)
 */
@property SKTCaptureDeviceType DeviceType;
@end

/**
 @class SKTCaptureEventData
 @brief Contains the definition of the data attached to a Capture event.
 */
@interface SKTCaptureEventData : NSObject
/**
 @brief Type of the data (Byte, Long, Array etc...)
 */
@property SKTCaptureEventDataType Type;

/**
 @brief Byte value, only relevant if the Type is <b>SKTCaptureEventDataTypeByte</b>
 */
@property int8_t ByteValue;

/**
 @brief Ulong value, only relevant if the Type is <b>SKTCaptureEventDataTypeUlong</b>
 */
@property unsigned long ULongValue;

/**
 @brief String value, only relevant if the Type is <b>SKTCaptureEventDataTypeString</b>
 */
@property (nullable, nonatomic, strong) NSString* StringValue;

/**
 @brief Array value, only relevant if the Type is <b>SKTCaptureEventDataTypeArray</b>
 */
@property (nullable, nonatomic, strong) NSData* ArrayValue;

/**
 @brief Decoded data value, only relevant if the Type is <b>SKTCaptureEventDataTypeDecodedData</b>
 */
@property (nullable, nonatomic, strong) SKTCaptureDecodedData* DecodedData;

/**
 @brief Device info value, only relevant if the Type is <b>SKTCaptureEventDataTypeDeviceInfo</b>
 */
@property (nullable, nonatomic, strong) SKTCaptureDeviceInfo* DeviceInfo;
@end

#endif /* SktCaptureEvent_h */
