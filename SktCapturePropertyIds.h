//
//  SktCapturePropertyIds.h
//  CaptureService
//
//  Copyright © 2017 Socket Mobile. All rights reserved.
//

#ifndef SktCapturePropertyIds_h
#define SktCapturePropertyIds_h



typedef NS_ENUM(NSInteger, SKTCapturePropertyID) {
	/**
	property to close and abort the listener thread

	Device: False	Get Type: NotApplicable 	Set Type: None
	*/
	SKTCapturePropertyIDAbort = -2146435072,

	/**
	property to get the Capture version

	Device: False	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDVersion = -2147418111,

	/**
	property to get the Capture Interface version

	Device: False	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDInterfaceVersion = -2147418110,

	/**
	property to set or get the Capture configuration

	Device: False	Get Type: String 	Set Type: String
	*/
	SKTCapturePropertyIDConfiguration = -2141913085,

	/**
	property to set or get the Data Confirmation mode

	Device: False	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDDataConfirmationMode = -2147352572,

	/**
	property to set or get the Data Confirmation Action

	Device: False	Get Type: None 	Set Type: Ulong
	*/
	SKTCapturePropertyIDDataConfirmationAction = -2147287035,

	/**
	property to set or get the Monitor mode (Debugging purpose)

	Device: False	Get Type: Byte 	Set Type: Array
	*/
	SKTCapturePropertyIDMonitorMode = -2145124346,

	/**
	property to get or set the SoftScan status (only for iOS and Android platforms)

	Device: False	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDSoftScanStatus = -2147352569,

	/**
	property to get a Capture Device version

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDVersionDevice = 65536,

	/**
	property to get a Capture Device type

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDDeviceType = 65538,

	/**
	property to send (get or set) a command using the Device specific commands set

	Device: True	Get Type: Array 	Set Type: Array
	*/
	SKTCapturePropertyIDDeviceSpecific = 4456451,

	/**
	property to get or set the data source status / information

	Device: True	Get Type: DataSource 	Set Type: DataSource
	*/
	SKTCapturePropertyIDDataSourceDevice = 7798788,

	/**
	property to trigger (set only) a Capture Device read or scan

	Device: True	Get Type: NotApplicable 	Set Type: Byte
	*/
	SKTCapturePropertyIDTriggerDevice = 1179653,

	/**
	property to apply a config to a Capture Device (not yet enabled)

	Device: True	Get Type: NotApplicable 	Set Type: None
	*/
	SKTCapturePropertyIDApplyConfigDevice = 1048582,

	/**
	property to set or get a preamble of a Capture Device decoded data

	Device: True	Get Type: None 	Set Type: String
	*/
	SKTCapturePropertyIDPreambleDevice = 327687,

	/**
	property to set or get the postamble of a Capture Device decoded data

	Device: True	Get Type: None 	Set Type: String
	*/
	SKTCapturePropertyIDPostambleDevice = 327688,

	/**
	property to get the Capture Device capabilities

	Device: True	Get Type: Byte 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDCapabilitiesDevice = 2162697,

	/**
	property to get the Capture Device Change ID

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDChangeIdDevice = 65546,

	/**
	property to get or set the Decoded Data Format of a Capture Device

	Device: True	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDDataFormatDevice = 131083,

	/**
	property to get or set the friendly name of a Capture Device

	Device: True	Get Type: None 	Set Type: String
	*/
	SKTCapturePropertyIDFriendlyNameDevice = 327936,

	/**
	property to get or set the Capture Device Security Mode

	Device: True	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDSecurityModeDevice = 131329,

	/**
	property to get or set the Capture Device PIN code

	Device: True	Get Type: NotApplicable 	Set Type: String
	*/
	SKTCapturePropertyIDPinCodeDevice = 1376514,

	/**
	property to set (delete) the Capture Device Pairing Bonding information

	Device: True	Get Type: NotApplicable 	Set Type: Byte
	*/
	SKTCapturePropertyIDDeletePairingBondingDevice = 1179907,

	/**
	property to set (Restore) the Capture Device Factory Default Settings

	Device: True	Get Type: NotApplicable 	Set Type: None
	*/
	SKTCapturePropertyIDRestoreFactoryDefaultsDevice = 1048836,

	/**
	 property to set (Power off) the Capture Device power off

	Device: True	Get Type: NotApplicable 	Set Type: None
	*/
	SKTCapturePropertyIDSetPowerOffDevice = 1048837,

	/**
	property to get the Capture Device Buttons status

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDButtonsStatusDevice = 65798,

	/**
	property to get or set the Capture Device Sound Configuration

	Device: True	Get Type: Byte 	Set Type: Array
	*/
	SKTCapturePropertyIDSoundConfigDevice = 2359559,

	/**
	 property to get or set the Capture Device Timers (Power off timer...)

	Device: True	Get Type: None 	Set Type: Array
	*/
	SKTCapturePropertyIDTimersDevice = 262408,

	/**
	 property to get or set the Capture Device Local (on the device) acknowledgment

	Device: True	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDLocalAcknowledgmentDevice = 131337,

	/**
	property to set (confirm) the Capture Device Decoded Data

	Device: True	Get Type: NotApplicable 	Set Type: Ulong
	*/
	SKTCapturePropertyIDDataConfirmationDevice = 1245450,

	/**
	 property to get the Capture Device Battery Level

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDBatteryLevelDevice = 65803,

	/**
	property to get or set the Capture Device Local Decode Action

	Device: True	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDLocalDecodeActionDevice = 131340,

	/**
	property to get the Capture Device Bluetooth Address

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDBluetoothAddressDevice = 65805,

	/**
	property to get the Capture Device Statistic Counters

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDStatisticCountersDevice = 65806,

	/**
	property to get or set the Capture Device Rumble Configuration

	Device: True	Get Type: Byte 	Set Type: Array
	*/
	SKTCapturePropertyIDRumbleConfigDevice = 2359567,

	/**
	property to get or set the Capture Device Profile Configuration

	Device: True	Get Type: None 	Set Type: Array
	*/
	SKTCapturePropertyIDProfileConfigDevice = 262416,

	/**
	property to set (disconnect) the Capture Device dropping off the connection from the host

	Device: True	Get Type: NotApplicable 	Set Type: Byte
	*/
	SKTCapturePropertyIDDisconnectDevice = 1179921,

	/**
	property to get or set the Capture Device store

	Device: True	Get Type: Array 	Set Type: Array
	*/
	SKTCapturePropertyIDDataStoreDevice = 4456722,

	/**
	property to set or get the Capture Device notification setting

	Device: True	Get Type: None 	Set Type: Ulong
	*/
	SKTCapturePropertyIDNotificationsDevice = 196883,

	/**
	property to get the Capture Device Connect reason

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDConnectReasonDevice = 65812,

	/**
	property to get the Capture Device Power State

	Device: True	Get Type: None 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDPowerStateDevice = 65813,

	/**
	property tp get or set the Capture Device Start Up Role SPP

	Device: True	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDStartUpRoleSPPDevice = 131350,

	/**
	property to get or set the Capture Device Connection Beep Configuration

	Device: True	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDConnectionBeepConfigDevice = 131351,

	/**
	property to get or set the Capture Device Flash

	Device: True	Get Type: None 	Set Type: Byte
	*/
	SKTCapturePropertyIDFlashDevice = 131352,

	/**
	property to get or set the Capture Device Overlay View (SoftScan only)

	Device: True	Get Type: None 	Set Type: Object
	*/
	SKTCapturePropertyIDOverlayViewDevice = 590105,

	/**
	property to get or set the Capture Device Stand Configuration

	Device: True	Get Type: None 	Set Type: Ulong
	*/
	SKTCapturePropertyIDStandConfigDevice = 196890,

	/**
	property to start a BLE discovery from a Device Manager

	Device: True	Get Type: NotApplicable 	Set Type: Ulong
	*/
	SKTCapturePropertyIDStartDiscovery = 1245696,

	/**
	property to set or get the BLE favorites for a Device Manager

	Device: True	Get Type: None 	Set Type: String
	*/
	SKTCapturePropertyIDFavorite = 328193,

	/**
	property to get the BLE Unique Device Identifier that can be used to set favorite with

	Device: True	Get Type: String 	Set Type: NotApplicable
	*/
	SKTCapturePropertyIDUniqueDeviceIdentifier = 5308930,


};

#endif
