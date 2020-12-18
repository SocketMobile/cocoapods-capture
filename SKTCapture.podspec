Pod::Spec.new do |s|
  s.name         = "SKTCapture"
  s.version      = "1.3.3"
  s.summary      = "Capture SDK Swift for Socket Mobile wireless devices."
  s.homepage     = "https://www.socketmobile.com"
  s.license      = { :type => "COMMERCIAL", :file => "LICENSE" }
  s.author       = { "Socket" => "developers@socketmobile.com" }
  s.documentation_url   = "https://docs.socketmobile.com/capture/ios/en/latest/"
  s.platform     = :ios, "10.0"
  s.source       = {
      :git => "https://github.com/SocketMobile/cocoapods-capture.git",
      :tag => "1.3.3"
  }
  s.ios.deployment_target = "10.0"
  s.swift_version = '5.0'
  s.pod_target_xcconfig = { 'SWIFT_VERSION' => '5.0', 'SWIFT_OPTIMIZATION_LEVEL' => '-Owholemodule' }

  s.static_framework = true

  s.source_files  = "**/*.{h,swift}"
  s.preserve_path = "**/*.a"

  s.resources = ['*.wav', '*.pem']
  s.vendored_frameworks = 'lib/SKTCapture.xcframework'

  s.ios.libraries = "c++","icucore"
  s.frameworks = "ExternalAccessory", "AudioToolbox", "AVFoundation", "CoreBluetooth"

  s.pod_target_xcconfig = {
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64'
  }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }


end
