/**
  CaptureHelper.swift

  Copyright © 2017 Socket Mobile, Inc.

*/

import Foundation

// MARK: - Capture Helper Delegates

/**
 Capture Helper base protocol does not have
 any delegate, it could be used for View Controllers
 that don't require any notification from Capture
 */
public protocol CaptureHelperDelegate {

}

/// Capture Helper protocol to comply in order to receive any error coming
/// from Capture
public protocol CaptureHelperErrorDelegate: CaptureHelperDelegate {

    /// delegate called when an unexpected error arises
    ///
    /// - Parameter error: contains the error code
    func didReceiveError(_ error: SKTResult);
}


/// Capture Helper protocol to comply in order to receive the device arrival, removal notifications
public protocol CaptureHelperDevicePresenceDelegate: CaptureHelperDelegate {

    /// delegate called when a device connects to the host
    ///
    /// - Parameters:
    ///   - device: contains the device information, such as friendly name and device type
    ///   - result: contains the result of the device connecting to the host
    func didNotifyArrivalForDevice(_ device: CaptureHelperDevice, withResult result: SKTResult)


    /// delegate called when a device disconnects from the host
    ///
    /// - Parameters:
    ///   - device: contains the device information, such as friendly name and device type
    ///   - result: contains the result of the device disconnecting from the host
    func didNotifyRemovalForDevice(_ device: CaptureHelperDevice, withResult result: SKTResult)

}

/// Capture Helper protocol to comply in order to receive the device manager arrival, removal notifications
public protocol CaptureHelperDeviceManagerPresenceDelegate: CaptureHelperDelegate {

    /// delegate called when a device manager connects to the host
    ///
    /// - Parameters:
    ///   - device: contains the device manager information, such as device type
    ///   - result: contains the result of the device manager connecting to the host
    func didNotifyArrivalForDeviceManager(_ device: CaptureHelperDeviceManager, withResult result: SKTResult)


    /// delegate called when a device manager disconnects from the host
    ///
    /// - Parameters:
    ///   - device: contains the device manager information, such as device type
    ///   - result: contains the result of the device manager disconnecting from the host
    func didNotifyRemovalForDeviceManager(_ device: CaptureHelperDeviceManager, withResult result: SKTResult)

}

/// Capture Helper protocol to comply in order to receive the device manager discovery notifications
public protocol CaptureHelperDeviceManagerDiscoveryDelegate: CaptureHelperDelegate {

    /// delegate called when a device manager discovered a device
    ///
    /// - Parameters:
    ///   - device: contains the device information, such as device type
    ///   - deviceManager: contains the device manager information from which the discovery was launched
    func didDiscoverDevice(_ device: String, fromDeviceManager deviceManager: CaptureHelperDeviceManager)


    /// delegate called when a device manager ended the discovery
    ///
    /// - Parameters:
    ///   - result: contains the result of the device manager disconnecting from the host
    ///   - deviceManager: contains the device manager information from which the discovery ended
    func didEndDiscoveryWithResult(_ result: SKTResult, fromDeviceManager deviceManager: CaptureHelperDeviceManager)

}

/// Capture Helper protocol to comply in order to receive the decoded data
public protocol CaptureHelperDeviceDecodedDataDelegate: CaptureHelperDelegate {

    /// delegate called when the decoded data is received from a device
    ///
    /// - Parameters:
    ///   - decodedData: contains the decoded data with its related information
    ///   - device: contains the device information from which the data has been decoded
    ///   - result: contains the result of the decoded data, most of the time it's success
    /// but in the case of SoftScan the result can be E_CANCELLED when the user cancel
    /// the scan.
    func didReceiveDecodedData( _ decodedData: SKTCaptureDecodedData?, fromDevice device: CaptureHelperDevice, withResult result: SKTResult)
}

/// Capture Helper protocol to comply in order to receive the power and battery information
public protocol CaptureHelperDevicePowerDelegate: CaptureHelperDelegate {


    /// delegate called when the power state has changed, this is happening when plug in the device to a power adapter
    ///
    /// - Parameters:
    ///   - powerState: contains the new power state of the device, @see SKTCapturePowerState
    ///   - device: contains the device information for which the power state has changed
    func didChangePowerState(_ powerState: SKTCapturePowerState, forDevice device: CaptureHelperDevice)


    /// delegate called when the battery level has changed
    ///
    /// - Parameters:
    ///   - batteryLevel: contains the battery level in %
    ///   - device: contains the device information for which the battery level has changed
    func didChangeBatteryLevel(_ batteryLevel: Int, forDevice device: CaptureHelperDevice)
}


/// Capture Helper protocol to comply in order to receive the buttons state
public protocol CaptureHelperDeviceButtonsDelegate : CaptureHelperDelegate {

    /// delegate called when the state of the device's buttons has changed
    ///
    /// - Parameters:
    ///   - buttonsState: contains the new buttons state
    ///   - device: contains the device information from which the buttons state has changed
    func didChangeButtonsState(_ buttonsState: SKTCaptureButtonsState, forDevice device: CaptureHelperDevice)
}

/// Capture Helper protocol to comply in order to receive all the Capture delegates
/// use this protocol if the applications needs to handle all the notifications
/// coming from Capture
public protocol CaptureHelperAllDelegate : CaptureHelperErrorDelegate, CaptureHelperDevicePresenceDelegate,
    CaptureHelperDevicePowerDelegate, CaptureHelperDeviceDecodedDataDelegate,
CaptureHelperDeviceButtonsDelegate {

}

// MARK: - Capture Helper Device

/**
 Capture Helper device, represents a device that is attached to Capture
 */
public class CaptureHelperDevice : NSObject {
    fileprivate var capture : SKTCapture

    /// can store an object that can be used for extension
    public var extensionProperties : Dictionary<String, Any>

    /// contains information about the device
    /// such as the device friendly name and device type
    public var deviceInfo = SKTCaptureDeviceInfo()

    /// specify the main Dispatch queue so the UI controls
    /// can be updated directly inside the completion handlers
    public var dispatchQueue : DispatchQueue?

    fileprivate override init() {
        self.capture = SKTCapture()
        self.extensionProperties = Dictionary<String, Any>()

        super.init()
    }

    convenience init(deviceInfo: SKTCaptureDeviceInfo, capture: SKTCapture){
        self.init()
        self.deviceInfo = deviceInfo
        self.capture = capture
    }


    /// retrieve the device friendly name
    ///
    /// - Parameter completion: closure receiving the response with the result and the friendly name of
    ///    the device if the result is successful
    open func getFriendlyNameWithCompletionHandler(_ completion: @escaping (_ result: SKTResult, _ name: String?)->Void){
        let property = SKTCaptureProperty()
        property.id = .friendlyNameDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.stringValue)
                }
            } else {
                completion(result, propertyResult?.stringValue)
            }
        }
    }

    /// set the device friendly name. The device friendly name has a limit of
    ///  32 UTF8 characters including the null terminated character, an error is
    ///  generated if the friendly name is too long.
    ///
    /// - Parameters:
    ///   - name: friendly name to set the device with
    ///   - completion: closure receiving the result of setting the new friendly name
    open func setFriendlyName(_ name: String, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .friendlyNameDevice
        property.type = .string
        property.stringValue = name
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// get the device Bluetooth address
    ///
    /// - Parameter completion: receiving the result of getting the device Bluetooth Address if the result
    open func getBluetoothAddressWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ bluetoothAddress: Data?)->Void){
        let property = SKTCaptureProperty()
        property.id = .bluetoothAddressDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.arrayValue)
                }
            } else {
                completion(result, propertyResult?.arrayValue)
            }
        }
    }

    /// get the device Type
    ///
    /// - Parameter completion: receiving the result and the device Type if the result is successful
    open func getTypeWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ deviceType: UInt?)->Void){
        let property = SKTCaptureProperty()
        property.id = .deviceType
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.uLongValue)
                }
            } else {
                completion(result, propertyResult?.uLongValue)
            }
        }
    }

    /// get the device Firmware version
    ///
    /// - Parameter completion: receiving the result and the device Firmware version if the result is successful
    open func getFirmwareVersionWithCompletionHandler(_ completion: @escaping(_ result: SKTResult,_ version: SKTCaptureVersion?)->Void){
        let property = SKTCaptureProperty()
        property.id = .versionDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.version)
                }
            } else {
                completion(result, propertyResult?.version)
            }
        }
    }

    /// get the device battery level
    ///
    /// note: to avoid pulling the battery level, some devices support a battery level change
    /// notification.
    ///
    /// - Parameter completion: receiving the result and the device battery level if the result is successful
    open func getBatteryLevelWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ batteryLevel: UInt?)->Void){
        let property = SKTCaptureProperty()
        property.id = .batteryLevelDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.uLongValue)
                }
            } else {
                completion(result, propertyResult?.uLongValue)
            }
        }
    }

    /// get the device power state
    ///
    /// note: to avoid pulling the power state, some devices support a power state change
    /// notification.
    ///
    /// - Parameter completion: receiving the result and the device power state if the result is successful
    open func getPowerStateWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ powerState: UInt?)->Void){
        let property = SKTCaptureProperty()
        property.id = .powerStateDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.uLongValue)
                }
            } else {
                completion(result, propertyResult?.uLongValue)
            }
        }
    }

    /// get the device buttons state
    ///
    /// note: some devices support buttons state change notifications
    ///
    /// - Parameter completion: receiving the result and the device buttons state if the result is successful
    open func getButtonsStateWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ buttonsState: SKTCaptureButtonsState?)->Void){
        let property = SKTCaptureProperty()
        property.id = .buttonsStatusDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            var buttonsState = nil as SKTCaptureButtonsState?
            if result == SKTCaptureErrors.E_NOERROR {
                if let byteValue = propertyResult?.byteValue {
                    buttonsState = SKTCaptureButtonsState(rawValue: Int(byteValue))
                }
            }
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, buttonsState)
                }
            } else {
                completion(result, buttonsState)
            }
        }
    }

    /// get the device stand configuration
    ///
    /// - Parameter completion: receiving the result and the device stand configuration if the result is successful
    open func getStandConfigWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ config: SKTCaptureStandConfig?)->Void){
        let property = SKTCaptureProperty()
        property.id = .standConfigDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            var standConfig = nil as SKTCaptureStandConfig?
            if result == SKTCaptureErrors.E_NOERROR {
                if let ulongValue = propertyResult?.uLongValue {
                    standConfig = SKTCaptureStandConfig(rawValue: Int(ulongValue))
                }
            }
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, standConfig)
                }
            } else {
                completion(result, standConfig)
            }
        }
    }

    /// set the device stand configuration
    ///
    /// - Parameters:
    ///   - config: config stand configuration to set the device with
    ///   - completion: block receiving the result of changing the device stand configuration
    open func setStandConfig(_ config: SKTCaptureStandConfig, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .standConfigDevice
        property.type = .ulong
        property.uLongValue = UInt(config.rawValue)
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// get the device decode action
    ///
    /// - Parameter completion: receiving the result and the device decode action if the result is successful
    open func getDecodeActionWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ decodeAction: SKTCaptureLocalDecodeAction?)->Void){
        let property = SKTCaptureProperty()
        property.id = .localDecodeActionDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            var decodeAction = nil as SKTCaptureLocalDecodeAction?
            if result == SKTCaptureErrors.E_NOERROR {
                if let byteValue = propertyResult?.byteValue {
                    decodeAction = SKTCaptureLocalDecodeAction(rawValue: Int(byteValue))
                }
            }
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, decodeAction)
                }
            } else {
                completion(result, decodeAction)
            }
        }
    }

    /// set the device decode action
    ///
    /// - Parameters:
    ///   - decodeAction: decode action to set the device with
    ///   - completion: receiving the result of changing the device decode action
    open func setDecodeAction(_ decodeAction: SKTCaptureLocalDecodeAction, withCompletionHandler completion:@escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .localDecodeActionDevice
        property.type = .byte
        property.byteValue = Int8(decodeAction.rawValue)
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// get the device local data acknowledgment
    ///
    /// - Parameter completion: receiving the result and the device local acknowledgment if the result is successful
    open func getDataAcknowledgmentWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ dataAcknownledgement: SKTCaptureDeviceDataAcknowledgment?)->Void){
        let property = SKTCaptureProperty()
        property.id = .dataConfirmationDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            var dataAck = nil as SKTCaptureDeviceDataAcknowledgment?
            if result == SKTCaptureErrors.E_NOERROR {
                if let uLongValue = propertyResult?.uLongValue {
                    dataAck = SKTCaptureDeviceDataAcknowledgment(rawValue: Int(uLongValue))
                }
            }
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, dataAck)
                }
            } else {
                completion(result, dataAck)
            }
        }
    }

    /// set the device local data acknowledgment
    ///
    /// - Parameters:
    ///   - dataAcknowledgment: set how the device acknwoledges data locally on the device
    ///   - completion: receiving the result of changing the device stand configuration
    open func setDataAcknowledgment(_ dataAcknowledgment: SKTCaptureDeviceDataAcknowledgment, withCompletionHandler completion:@escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .dataConfirmationDevice
        property.type = .ulong
        property.uLongValue = UInt(dataAcknowledgment.rawValue)
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// get the device postamble
    ///
    /// - Parameter completion: receiving the result and the device postamble if the result is successful
    open func getPostambleWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ postamble: String?)->Void){
        let property = SKTCaptureProperty()
        property.id = .postambleDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.stringValue)
                }
            } else {
                completion(result, propertyResult?.stringValue)
            }
        }
    }

    /// set the device postamble
    ///
    /// - Parameters:
    ///   - postamble: postamble to set the device with
    ///   - completion: receiving the result of changing the device postamble
    open func setPostamble(_ postamble: String, withCompletionHandler completion:@escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .postambleDevice
        property.type = .string
        property.stringValue = postamble
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// get the device data source information
    ///
    /// - Parameters:
    ///   - data source Id: contains the data source ID for which the information would be retrieved
    ///   - completion: receiving the result and the device data source information if the result is successful
    open func getDataSourceInfoFromId(_ dataSourceId: SKTCaptureDataSourceID, withCompletionHandler completion:@escaping(_ result: SKTResult, _ dataSourceInfo: SKTCaptureDataSource?)->Void){
        let dataSource = SKTCaptureDataSource()
        let property = SKTCaptureProperty()
        property.id = .dataSourceDevice
        property.type = .dataSource

        dataSource.id = dataSourceId
        dataSource.flags = .status
        property.dataSource = dataSource
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.dataSource)
                }
            } else {
                completion(result, propertyResult?.dataSource)
            }
        }
    }

    /// set the device data source information
    ///
    /// - Parameters:
    ///   - dataSource: data source to enable or disable
    ///   - completion: receiving the result of changing the device data source
    open func setDataSourceInfo(_ dataSource: SKTCaptureDataSource, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .dataSourceDevice
        property.type = .dataSource
        property.dataSource = dataSource
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// set the device trigger
    ///
    /// this operation can programmatically start a device read operation, or it can
    /// disable the device trigger button until it gets re-enable again by using this
    /// function too.
    ///
    /// - Parameters:
    ///   - trigger: contains the trigger command to apply
    ///   - completion: receiving the result of setting the trigger
    open func setTrigger(_ trigger: SKTCaptureTrigger, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .triggerDevice
        property.type = .byte
        property.byteValue = Int8(trigger.rawValue)
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// set the decoded data confirmation
    ///
    /// This function is required to acknowledge the decoded data that has been received
    /// when the data confirmation mode has been set to SKTCaptureDataConfirmationModeApp
    ///
    /// This function could also be called at any point of time if something needs to
    /// be reported to the user. By example making the scanner beep or vibrate to get
    /// the user to look at a screen.
    ///
    /// note: Good AND Bad settings can not be used together.
    ///
    /// - Parameters:
    ///   - led: contains the led to light (None, Green, Red)
    ///   - beep: contains the beep to perform (None, Good, Bad)
    ///   - rumble: contains the rumble to perform (None, Good, Bad)
    ///   - completion: receiving the result of setting the decoded data confirmation
    open func setDataConfirmationWithLed(_ led: SKTCaptureDataConfirmationLed, withBeep beep:SKTCaptureDataConfirmationBeep, withRumble rumble: SKTCaptureDataConfirmationRumble, withCompletionHandler completion:@escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .dataConfirmationDevice
        property.type = .ulong
        property.uLongValue = UInt(SKTHelper.getDataComfirmation(withReserve: 0, withRumble: rumble.rawValue, withBeep: beep.rawValue, withLed: led.rawValue))
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// set the device notifications
    ///
    /// - Parameters:
    ///   - notifications: select the notifications to receive
    ///   - completion: receiving the result of setting the notifications
    open func setNotifications(_ notifications: SKTCaptureNotifications, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .notificationsDevice
        property.type = .ulong
        property.uLongValue = UInt(notifications.rawValue)
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// get the device notifications selection
    ///
    /// - Parameter completion: receiving the result and the device notifications setting if the result is successful
    open func getNotificationsWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ notifications: SKTCaptureNotifications?)->Void){
        let property = SKTCaptureProperty()
        property.id = .notificationsDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            var notifications = nil as SKTCaptureNotifications?
            if let longValue = propertyResult?.uLongValue {
                notifications = SKTCaptureNotifications(rawValue: Int(longValue))
            }
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, notifications)
                }
            } else {
                completion(result, notifications)
            }
        }
    }

    /// set the SoftScan overlay view parameters mainly for the ViewFinder view
    ///
    /// - Parameters:
    ///   - parameters: dictionary containing the parameters for the ViewFinder
    ///   - completion: closure receiving the result of setting the Overlay View parameters
    open func setSoftScanOverlayViewParameter(_ parameters: Dictionary<String, Any>, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .overlayViewDevice
        property.type = .object
        property.object = parameters as NSObject
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    /// get the SoftScan overlay view parameters used mainly for the ViewFinder view
    ///
    /// - Parameter completion: closure receiving the result and the overlay view parameters
    open func getSoftScanOverlayViewParameterWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ parameter: Dictionary<String, Any>?)->Void){
        let property = SKTCaptureProperty()
        property.id = .overlayViewDevice
        property.type = .none
        capture.getProperty(property) { (result, propertyResult) in
            var parameters = nil as Dictionary<String,Any>?
            if let obj = propertyResult?.object {
                parameters = obj as? Dictionary<String,Any>
            }
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, parameters)
                }
            } else {
                completion(result, parameters)
            }
        }
    }

    /// send a specific command to the device
    ///
    /// These commands are specific to a device, therefore the device should first be identified
    /// before sending such commands otherwise an unpredicable result could happen if they are
    /// sent to a different device.
    ///
    /// - Parameters:
    ///   - command: an array of bytes that holds the specific command to send to the device
    ///   - completion: receiving the result and the device specific command response if the result is successful
    open func getDeviceSpecificCommand(_ command: Data, withCompletionHandler completion: @escaping(_ result: SKTResult, _ commandResult: Data?)->Void){
        let property = SKTCaptureProperty()
        property.id = .deviceSpecific
        property.type = .array
        property.arrayValue = command
        capture.getProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async{
                    completion(result, propertyResult?.arrayValue)
                }
            } else {
                completion(result, propertyResult?.arrayValue)
            }
        }
    }
}

// MARK: - Capture Helper Device Manager
public class CaptureHelperDeviceManager : CaptureHelperDevice {

    open func startDiscoveryWithTimeout(_ timeout: NSInteger, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .startDiscovery
        property.type = .ulong
        property.uLongValue = UInt(timeout)
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async {
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    open func setFavoriteDevices(_ favorites: String, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        let property = SKTCaptureProperty()
        property.id = .favorite
        property.type = .string
        property.stringValue = favorites
        capture.setProperty(property) { (result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async {
                    completion(result)
                }
            } else {
                completion(result)
            }
        }
    }

    open func getFavoriteDevicesWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ favorites: String?)->Void){
        let property = SKTCaptureProperty()
        property.id = .favorite
        property.type = .none
        capture.getProperty(property) {(result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async {
                    completion(result, propertyResult?.stringValue)
                }
            } else {
                completion(result, propertyResult?.stringValue)
            }
        }
    }

    open func getDeviceUniqueIdentifierFromDeviceGuid(_ deviceGuid: String, withCompletionHandler completion: @escaping(_ result: SKTResult, _ deviceUniqueIdentifier: String?)->Void){
        let property = SKTCaptureProperty()
        property.id = .uniqueDeviceIdentifier
        property.type = .string
        property.stringValue = deviceGuid
        capture.getProperty(property) {(result, propertyResult) in
            if let dq = self.dispatchQueue {
                dq.async {
                    completion(result, propertyResult?.stringValue)
                }
            } else {
                completion(result, propertyResult?.stringValue)
            }
        }
    }
}

// MARK: - Capture Helper Main Entry Point

/// Main entry point for using Capture
/// 1- get a Capture instance by using CaptureHelper.sharedInstance
/// 2- push a View Controller delegate reference that is compliant to a CaptureHelperDelegate protocol
/// 3- fill a SKTAppInfo with developer ID, bundle ID and AppKey coming from Socket Mobile developer portal
/// 4- open Capture with the SKTAppInfo instance
public class CaptureHelper : NSObject, SKTCaptureDelegate {
    private var capture : SKTCapture?
    private var openCount = 0;

    fileprivate var delegatesStack = Array<CaptureHelperDelegate>()
    fileprivate var currentDelegate : CaptureHelperDelegate?
    fileprivate var devices = Dictionary<SKTCapture, CaptureHelperDevice>()
    fileprivate var deviceManagers = Dictionary<SKTCapture, CaptureHelperDeviceManager>()

    /// can store any object that can be used in an extension
    public var extensionProperties : Dictionary<String, Any>

    /// dispatch queue that can be set to the
    /// main queue so the completion handlers
    /// can update directly the UI controls
    /// set this property to DispatchQueue.main
    public var dispatchQueue : DispatchQueue?

    /// dispatch queue that can be set to the
    /// the main queue so the Capture Helper
    /// delegates can update directly the UI controls
    /// set this property to DispatchQueue.main
    public var delegateDispatchQueue: DispatchQueue?

    /// static shared instance of CaptureHelper
    public static let sharedInstance = CaptureHelper()

    fileprivate override init() {
        extensionProperties = Dictionary<String, Any>()
    }

    /// reference to the Capture API that can be used in
    /// extension class
    public var captureApi : SKTCapture? {
        get {
            return capture;
        }
    }

    /// push a delegate reference into the delegates stack
    /// each new View can push its delegate reference and the
    /// last one pushed is the one used for receiving the Capture
    /// delegates.
    /// NOTE: If a device is already connected to the host, doing a pushDelegate
    /// will call the didNotifyArrivalForDevice if the delegate pushed supports
    /// this in its protocol.
    ///
    /// - Parameter delegate : reference to a delegate to push in the delegates stack
    /// - Returns:
    ///     hasBeenPushed : true is the delegate has been pushed, false otherwise
    @discardableResult open func pushDelegate(_ delegate: CaptureHelperDelegate) -> Bool {
        var hasBeenPushed = false
        // make sure the currentDelegate if not nil
        // that is not equal to delegate passed in argument
        if let current = currentDelegate {
            if (current as AnyObject === delegate as AnyObject) {
                return hasBeenPushed
            }
        }
        hasBeenPushed = true
        delegatesStack.append(delegate)
        currentDelegate = delegate

        if let delegate = self.currentDelegate as? CaptureHelperDevicePresenceDelegate {
            for device in devices {
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        delegate.didNotifyArrivalForDevice(device.value, withResult: SKTCaptureErrors.E_NOERROR)
                    }
                } else {
                    delegate.didNotifyArrivalForDevice(device.value, withResult: SKTCaptureErrors.E_NOERROR)
                }
            }
        }
        if let delegate = self.currentDelegate as? CaptureHelperDeviceManagerPresenceDelegate {
            for device in deviceManagers {
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        delegate.didNotifyArrivalForDeviceManager(device.value, withResult: SKTCaptureErrors.E_NOERROR)
                    }
                } else {
                    delegate.didNotifyArrivalForDeviceManager(device.value, withResult: SKTCaptureErrors.E_NOERROR)
                }
            }
        }
        return hasBeenPushed
    }


    /// remove the delegate from the delegates stack
    ///
    /// - Parameter delegate: reference to the class that receive
    /// the Capture Delegates
    ///
    /// - Returns:
    /// hasBeenPoped is true if the delegate has been poped from the
    //  delegates stack, false otherwise
    @discardableResult open func popDelegate(_ delegate: CaptureHelperDelegate) -> Bool {
        var hasBeenRemoved = false
        if delegatesStack.count > 0 {
            let last = delegatesStack.removeLast()
            if (last as AnyObject === delegate as AnyObject) {
                hasBeenRemoved = true
                currentDelegate = delegatesStack.last
            } else {
                delegatesStack.append(last)
            }
        }
        return hasBeenRemoved
    }


    /// get the list of devices this CaptureHelper has opened
    ///
    /// - Returns: list of CaptureHelperDevice opened by Capture Helper
    open func getDevices()->Array<CaptureHelperDevice> {
        let newDevices = Array<CaptureHelperDevice>(devices.values)
        return newDevices
    }

    /// get the list of device managers this CaptureHelper has opened
    ///
    /// - Returns: list of CaptureHelperDeviceManager opened by Capture Helper
    open func getDeviceManagers()->Array<CaptureHelperDeviceManager> {
        let newDeviceManagers = Array<CaptureHelperDeviceManager>(deviceManagers.values)
        return newDeviceManagers
    }

    /// open Capture
    ///
    /// Main entry point of the Capture SDK. This method should be called first.
    ///
    /// open Capture with the application information which contains
    /// the developer ID, the application Bundle ID and the AppKey that
    /// can be retrieved on the Socket Mobile developer portal
    ///
    /// The delegates should be pushed before calling this method to make sure
    /// none of the events are missed.
    /// - Parameters:
    ///   - appInfo: class containing developer ID, application Bundle ID and the AppKey
    ///   - completionHandler: called upon completion with the result code
    open func openWithAppInfo(_ appInfo: SKTAppInfo, withCompletionHandler completion: @escaping (_ result: SKTResult)->Void){
        if (capture == nil) {
            capture = SKTCapture(delegate: self)
            capture?.open(with: appInfo, completionHandler: {(result) in
                if result == SKTCaptureErrors.E_NOERROR {
                    self.openCount += 1;
                } else {
                    self.capture = nil;
                }
                self.callCompletion(withResult:result, withCompletion:completion)
            })
        } else {
            self.openCount += 1;
            self.callCompletion(withResult:SKTCaptureErrors.E_NOERROR, withCompletion:completion)
        }
    }


    /// close Capture, once this method is called the application won't
    /// receive anything from Capture
    ///
    /// - Parameter completionHandler: called upon complete with the result code
    open func closeWithCompletionHandler(_ completion: @escaping (_ result: SKTResult)->Void){
        if let cap = capture {
            self.openCount -= 1;
            if self.openCount == 0 {
                cap.close(completionHandler:{(result) in
                    self.capture = nil
                    self.callCompletion(withResult:result, withCompletion:completion)
                })
            } else {
                callCompletion(withResult: SKTCaptureErrors.E_NOERROR, withCompletion: completion);
            }
        }
        else {
            callCompletion(withResult: SKTCaptureErrors.E_NOERROR, withCompletion: completion);
        }
    }

    /// delegate from Capture that is called each time a Capture event is fired
    ///
    /// - Parameters:
    ///   - event: Capture event sent by Capture to the application
    ///   - capture: reference of the capture the event refers to
    ///   - result: result code of the event
    public func didReceive(_ event: SKTCaptureEvent!, for capture: SKTCapture!, withResult result: SKTResult) {
        switch event.id {
        case SKTCaptureEventID.error:
            if let delegate = currentDelegate as? CaptureHelperErrorDelegate {
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        delegate.didReceiveError(result)
                    }
                } else {
                    delegate.didReceiveError(result)
                }
            }
            break
        case SKTCaptureEventID.deviceArrival:
            if let deviceInfo = event.data?.deviceInfo {
                capture.openDevice(withGuid: deviceInfo.guid, completionHandler: {(result: SKTResult, device: SKTCapture?)->Void in
                    if (result == SKTCaptureErrors.E_NOERROR){
                        if let dev = device {
                            let newDevice = CaptureHelperDevice(deviceInfo: deviceInfo, capture: dev)
                            self.devices[dev] = newDevice
                            if let delegate = self.currentDelegate as? CaptureHelperDevicePresenceDelegate {
                                if let dq = self.delegateDispatchQueue {
                                    dq.async{
                                        delegate.didNotifyArrivalForDevice(newDevice, withResult: result)
                                    }
                                } else {
                                    delegate.didNotifyArrivalForDevice(newDevice, withResult: result)
                                }
                            }
                        } else {
                            // trace
                        }
                    }
                })
            }
            break
        case SKTCaptureEventID.deviceRemoval:
            if let deviceFound = self.devices[capture] {
                self.devices.removeValue(forKey: capture)
                if let delegate = self.currentDelegate as? CaptureHelperDevicePresenceDelegate {
                    if let dq = self.delegateDispatchQueue {
                        dq.async{
                            delegate.didNotifyRemovalForDevice(deviceFound, withResult: result)
                        }
                    } else {
                        delegate.didNotifyRemovalForDevice(deviceFound, withResult: result)
                    }
                }
                capture.close(completionHandler: { (result) in
                    if (result != SKTCaptureErrors.E_NOERROR) {
                        print("closing the device returns \(result.rawValue)")
                    }
                })
            }
            break
        case SKTCaptureEventID.deviceManagerArrival:
            if let deviceInfo = event.data?.deviceInfo {
                capture.openDevice(withGuid: deviceInfo.guid, completionHandler: {(result: SKTResult, device: SKTCapture?)->Void in
                    if (result == SKTCaptureErrors.E_NOERROR){
                        if let dev = device {
                            let newDevice = CaptureHelperDeviceManager(deviceInfo: deviceInfo, capture: dev)
                            self.deviceManagers[dev] = newDevice
                            if let delegate = self.currentDelegate as? CaptureHelperDeviceManagerPresenceDelegate {
                                if let dq = self.delegateDispatchQueue {
                                    dq.async{
                                        delegate.didNotifyArrivalForDeviceManager(newDevice, withResult: result)
                                    }
                                } else {
                                    delegate.didNotifyArrivalForDeviceManager(newDevice, withResult: result)
                                }
                            }
                        } else {
                            // trace
                        }
                    }
                })
            }
            break
        case SKTCaptureEventID.deviceManagerRemoval:
            if let deviceFound = self.deviceManagers[capture] {
                if let delegate = self.currentDelegate as? CaptureHelperDeviceManagerPresenceDelegate {
                    if let dq = self.delegateDispatchQueue {
                        dq.async{
                            delegate.didNotifyRemovalForDeviceManager(deviceFound, withResult: result)
                        }
                    } else {
                        delegate.didNotifyRemovalForDeviceManager(deviceFound, withResult: result)
                    }
                }
                self.deviceManagers.removeValue(forKey: capture)
                capture.close(completionHandler: { (result) in
                    if (result != SKTCaptureErrors.E_NOERROR) {
                        print("closing the device manager returns \(result.rawValue)")
                    }
                })
            }
            break
        case SKTCaptureEventID.deviceDiscovered:
            if let deviceFound = self.deviceManagers[capture] {
                if let delegate = self.currentDelegate as? CaptureHelperDeviceManagerDiscoveryDelegate {
                    if let dq = self.delegateDispatchQueue {
                        dq.async{
                            delegate.didDiscoverDevice((event.data?.stringValue)!, fromDeviceManager: deviceFound)
                        }
                    } else {
                        delegate.didDiscoverDevice((event.data?.stringValue)!, fromDeviceManager: deviceFound)
                    }
                }
            }
            break;
        case SKTCaptureEventID.discoveryEnd:
            if let deviceFound = self.deviceManagers[capture] {
                if let delegate = self.currentDelegate as? CaptureHelperDeviceManagerDiscoveryDelegate {
                    if let dq = self.delegateDispatchQueue {
                        dq.async{
                            delegate.didEndDiscoveryWithResult(result, fromDeviceManager: deviceFound)
                        }
                    } else {
                        delegate.didEndDiscoveryWithResult(result, fromDeviceManager: deviceFound)
                    }
                }
            }
            break;
        case SKTCaptureEventID.decodedData:
            if let deviceFound = self.devices[capture] {
                if let delegate = self.currentDelegate as? CaptureHelperDeviceDecodedDataDelegate {
                    if let dq = self.delegateDispatchQueue {
                        dq.async{
                            delegate.didReceiveDecodedData(event.data?.decodedData, fromDevice: deviceFound, withResult: result)
                        }
                    } else {
                        delegate.didReceiveDecodedData(event.data?.decodedData, fromDevice: deviceFound, withResult: result)
                    }
                }
            }
            break
        case SKTCaptureEventID.batteryLevel:
            if let deviceFound = self.devices[capture] {
                if let delegate = currentDelegate as? CaptureHelperDevicePowerDelegate {
                    if let value = event.data?.uLongValue {
                        if let dq = self.delegateDispatchQueue {
                            dq.async{
                                delegate.didChangeBatteryLevel(Int(value), forDevice: deviceFound)
                            }
                        } else {
                            delegate.didChangeBatteryLevel(Int(value), forDevice: deviceFound)
                        }
                    }
                }
            }
            break
        case SKTCaptureEventID.power:
            if let deviceFound = self.devices[capture] {
                if let delegate = currentDelegate as? CaptureHelperDevicePowerDelegate {
                    if let value = event.data?.uLongValue {
                        if let dq = self.delegateDispatchQueue {
                            dq.async{
                                delegate.didChangePowerState(SKTCapturePowerState(rawValue: Int(value))!, forDevice: deviceFound)
                            }
                        } else {
                            delegate.didChangePowerState(SKTCapturePowerState(rawValue: Int(value))!, forDevice: deviceFound)
                        }
                    }
                }
            }
            break
        case SKTCaptureEventID.buttons:
            if let deviceFound = self.devices[capture] {
                if let delegate = currentDelegate as? CaptureHelperDeviceButtonsDelegate {
                    if let value = event.data?.byteValue {
                        let finalValue = SKTCaptureButtonsState(rawValue: Int(value))
                        if let dq = self.delegateDispatchQueue {
                            dq.async{
                                delegate.didChangeButtonsState(finalValue, forDevice: deviceFound)
                            }
                        } else {
                            delegate.didChangeButtonsState(finalValue, forDevice: deviceFound)
                        }
                    }
                }
            }
            break;
        default: break
            // not much to do
        }
    }


    /// retrieve the Capture version
    ///
    /// - Parameter completion: called upon completion of getting the Capture version
    /// with the result and the version as argument.
    open func getVersionWithCompletionHandler(_ completion:@escaping(_ result: SKTResult, _ version: SKTCaptureVersion?)->Void){
        if let cap = capture {
            let property = SKTCaptureProperty()
            property.id = .version
            property.type = .none
            cap.getProperty(property) { (result, propertyResult) in
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        completion(result, propertyResult?.version)
                    }
                } else {
                    completion(result, propertyResult?.version)
                }
            }
        }
        else {
            if let dq = self.delegateDispatchQueue {
                dq.async{
                    completion(SKTCaptureErrors.E_INVALIDHANDLE, nil)
                }
            } else {
                completion(SKTCaptureErrors.E_INVALIDHANDLE, nil)
            }
        }
    }

    /// retrieve the confirmation mode used to configure how the decoded data
    /// are confirmed.
    ///
    /// - Parameter completion: called upon completion of getting the confirmation mode
    /// with the result and the confirmation mode as argument.
    open func getConfirmationModeWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ confirmationMode: SKTCaptureDataConfirmation?)->Void){
        if let cap = capture {
            let property = SKTCaptureProperty()
            property.id = .dataConfirmationMode
            property.type = .none
            cap.getProperty(property) { (result, propertyResult) in
                var confirmation = nil as SKTCaptureDataConfirmation?
                if let byteValue = propertyResult?.byteValue {
                    confirmation = SKTCaptureDataConfirmation(rawValue: Int(byteValue))
                }
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        completion(result, confirmation)
                    }
                } else {
                    completion(result, confirmation)
                }
            }
        }
        else {
            if let dq = self.delegateDispatchQueue {
                dq.async{
                    completion(SKTCaptureErrors.E_INVALIDHANDLE, nil)
                }
            } else {
                completion(SKTCaptureErrors.E_INVALIDHANDLE, nil)
            }
        }
    }

    /// set the confirmation mode to define how the decoded data should be confirmed.
    ///
    /// - Parameters:
    ///   - confirmationMode: confirmationMode contains the confirmation mode to set Capture with
    ///   - completion: called upon completion of setting the confirmation mode
    /// with the result of setting the confirmation mode.
    open func setConfirmationMode(_ confirmationMode: SKTCaptureDataConfirmation, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        if let cap = capture {
            let property = SKTCaptureProperty()
            property.id = .dataConfirmationMode
            property.type = .byte
            property.byteValue = Int8(confirmationMode.rawValue)
            cap.setProperty(property) { (result, propertyResult) in
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        completion(result)
                    }
                } else {
                    completion(result)
                }
            }
        }
        else {
            if let dq = self.delegateDispatchQueue {
                dq.async{
                    completion(SKTCaptureErrors.E_INVALIDHANDLE)
                }
            } else {
                completion(SKTCaptureErrors.E_INVALIDHANDLE)
            }
        }
    }

    /// retrieve the SoftScan (Scanning using the host camera) status. The status could
    /// be "not supported", "supported", "disabled" and "enabled".
    ///
    /// - Parameter completion: called upon completion of getting the SoftScan status with
    /// result and SoftScan status as argument.
    open func getSoftScanStatusWithCompletionHandler(_ completion: @escaping(_ result: SKTResult, _ status: SKTCaptureSoftScan?)->Void){
        if let cap = capture {
            let property = SKTCaptureProperty()
            property.id = .softScanStatus
            property.type = .none
            cap.getProperty(property) { (result, propertyResult) in
                var status = nil as SKTCaptureSoftScan?
                if let byteValue = propertyResult?.byteValue {
                    status = SKTCaptureSoftScan(rawValue: Int(byteValue))
                }
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        completion(result, status)
                    }
                } else {
                    completion(result, status)
                }
            }
        }
        else {
            if let dq = self.delegateDispatchQueue {
                dq.async{
                    completion(SKTCaptureErrors.E_INVALIDHANDLE, nil)
                }
            } else {
                completion(SKTCaptureErrors.E_INVALIDHANDLE, nil)
            }
        }
    }

    /// set the SoftScan (Scanning using the host camera) status. The status could
    /// be "not supported", "supported", "disabled" and "enabled".
    ///
    /// - Parameters:
    ///   - status: contains the new SoftScan status
    ///   - completion: called upon completion of setting the SoftScan status with the
    /// result as argument.
    open func setSoftScanStatus(_ status: SKTCaptureSoftScan, withCompletionHandler completion: @escaping(_ result: SKTResult)->Void){
        if let cap = capture {
            let property = SKTCaptureProperty()
            property.id = .softScanStatus
            property.type = .byte
            property.byteValue = Int8(status.rawValue)
            cap.setProperty(property) { (result, propertyResult) in
                if let dq = self.delegateDispatchQueue {
                    dq.async{
                        completion(result)
                    }
                } else {
                    completion(result)
                }
            }
        }
        else {
            if let dq = self.delegateDispatchQueue {
                dq.async{
                    completion(SKTCaptureErrors.E_INVALIDHANDLE)
                }
            } else {
                completion(SKTCaptureErrors.E_INVALIDHANDLE)
            }
        }
    }
    
    /// call the completion block function with the result passed in argument.
    ///
    /// - Parameters:
    ///   - result: contains the result to call the completion block with
    ///   - completion: block called with the appropriate dispatch queue with the
    /// result as argument.
    func callCompletion(withResult result:SKTResult, withCompletion completion: @escaping (_ result: SKTResult)->Void) {
        if let dq = self.delegateDispatchQueue {
            dq.async{
                completion(result)
            }
        } else {
            completion(result)
        }
    }
    

}
