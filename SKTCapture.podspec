Pod::Spec.new do |s|
  s.name         = "SKTCapture"
  s.version      = "1.2.9"
  # s.module_name  = "SocketMobile"
  s.summary      = "Capture SDK Swift for Socket Mobile wireless devices."
  s.homepage     = "https://www.socketmobile.com"
  s.license      = { :type => "COMMERCIAL", :file => "LICENSE" }
  s.author       = { "Socket" => "developers@socketmobile.com" }
  s.documentation_url   = "https://docs.socketmobile.com/capture/ios/en/latest/"
  s.platform     = :ios, "9.1"
  s.swift_version = '4.0'
  s.source       = {
      :git => "ssh://git@git.socketmobile.com/scanning/cocoapods-capture.git",
      :tag => "1.2.9"
  }
  s.ios.deployment_target = "9.1"
  s.pod_target_xcconfig = { 'SWIFT_VERSION' => '4.0', 'SWIFT_OPTIMIZATION_LEVEL' => '-Owholemodule' }
  s.source_files  = "**/*.{h,swift}"
  s.public_header_files = "*.h"
  s.preserve_path = "**/*.a"
  s.resources = ['*.wav', '*.pem']
  s.ios.vendored_libraries = "lib/libCaptureCore.a", "lib/libCaptureServiceDirect.a"
  s.ios.libraries = "c++","icucore"
  s.frameworks = "ExternalAccessory", "AudioToolbox", "AVFoundation", "CoreBluetooth"
end
