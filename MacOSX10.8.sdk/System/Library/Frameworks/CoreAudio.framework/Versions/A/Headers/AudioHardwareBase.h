/*==================================================================================================
     File:       CoreAudio/AudioHardwareBase.h

     Copyright:  (c) 1985-2011 by Apple, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

==================================================================================================*/
#if !defined(__AudioHardwareBase_h__)
#define __AudioHardwareBase_h__

//==================================================================================================
#pragma mark -
#pragma mark Overview
/*!
    @header AudioHardwareBase
    
    This file defines the HAL's object model including the properties and their needed types and
    constants that describe the proeprty values.
*/

//==================================================================================================
//  Includes

#include <CoreAudio/CoreAudioTypes.h>

//==================================================================================================

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint off
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//==================================================================================================
#pragma mark -
#pragma mark Basic Types

/*!
    @typedef        AudioObjectID
    @abstract       A UInt32 that provides a handle on a specific AudioObject.
*/
typedef UInt32  AudioObjectID;

/*!
    @typedef        AudioClassID
    @abstract       AudioClassIDs are used to identify the class of an AudioObject.
*/
typedef UInt32  AudioClassID;

/*!
    @typedef        AudioObjectPropertySelector
    @abstract       An AudioObjectPropertySelector is a four char code that identifies, along with
                    the AudioObjectPropertyScope and AudioObjectPropertyElement, a specific piece of
                    information about an AudioObject.
    @discussion     The property selector specifies the general classification of the property such
                    as volume, stream format, latency, etc. Note that each class has a different set
                    of selectors. A subclass inherits it's super class's set of selectors, although
                    it may not implement them all.
*/
typedef UInt32  AudioObjectPropertySelector;

/*!
    @typedef        AudioObjectPropertyScope
    @abstract       An AudioObjectPropertyScope is a four char code that identifies, along with the
                    AudioObjectPropertySelector and AudioObjectPropertyElement, a specific piece of
                    information about an AudioObject.
    @discussion     The scope specifies the section of the object in which to look for the property,
                    such as input, output, global, etc. Note that each class has a different set of
                    scopes. A subclass inherits it's superclass's set of scopes.
*/
typedef UInt32  AudioObjectPropertyScope;

/*!
    @typedef        AudioObjectPropertyElement
    @abstract       An AudioObjectPropertyElement is an integer that identifies, along with the
                    AudioObjectPropertySelector and AudioObjectPropertyScope, a specific piece of
                    information about an AudioObject.
    @discussion     The element selects one of possibly many items in the section of the object in
                    which to look for the property. Elements are number sequentially where 0
                    represents the master element. Elements are particular to an instance of a
                    class, meaning that two instances can have different numbers of elements in the
                    same scope. There is no inheritance of elements.
*/
typedef UInt32  AudioObjectPropertyElement;

/*!
    @struct         AudioObjectPropertyAddress
    @abstract       An AudioObjectPropertyAddress collects the three parts that identify a specific
                    property together in a struct for easy transmission.
    @field          mSelector
                        The AudioObjectPropertySelector for the property.
    @field          mScope
                        The AudioObjectPropertyScope for the property.
    @field          mElement
                        The AudioObjectPropertyElement for the property.
*/
struct  AudioObjectPropertyAddress
{
    AudioObjectPropertySelector mSelector;
    AudioObjectPropertyScope    mScope;
    AudioObjectPropertyElement  mElement;
};
typedef struct AudioObjectPropertyAddress   AudioObjectPropertyAddress;

//==================================================================================================
#pragma mark Basic Constants

/*!
    @enum           Error Constants
    @abstract       The error constants unique to the HAL.
    @discussion     These are the error constants that are unique to the HAL. Note that the HAL's
                    functions can and will return other codes that are not listed here. While these
                    constants give a general idea of what might have gone wrong during the execution
                    of an API call, if an API call returns anything other than kAudioHardwareNoError
                    it is to be viewed as the same failure regardless of what constant is actually
                    returned.
    @constant       kAudioHardwareNoError
                        The function call completed successfully.
    @constant       kAudioHardwareNotRunningError
                        The function call requires that the hardware be running but it isn't.
    @constant       kAudioHardwareUnspecifiedError
                        The function call failed while doing something that doesn't provide any
                        error messages.
    @constant       kAudioHardwareUnknownPropertyError
                        The AudioObject doesn't know about the property at the given address.
    @constant       kAudioHardwareBadPropertySizeError
                        An improperly sized buffer was provided when accessing the data of a
                        property.
    @constant       kAudioHardwareIllegalOperationError
                        The requested operation couldn't be completed.
    @constant       kAudioHardwareBadObjectError
                        The AudioObjectID passed to the function doesn't map to a valid AudioObject.
    @constant       kAudioHardwareBadDeviceError
                        The AudioObjectID passed to the function doesn't map to a valid AudioDevice.
    @constant       kAudioHardwareBadStreamError
                        The AudioObjectID passed to the function doesn't map to a valid AudioStream.
    @constant       kAudioHardwareUnsupportedOperationError
                        The AudioObject doesn't support the requested operation.
    @constant       kAudioDeviceUnsupportedFormatError
                        The AudioStream doesn't support the requested format.
    @constant       kAudioDevicePermissionsError
                        The requested operation can't be completed because the process doesn't have
                        permission.
*/
enum
{
    kAudioHardwareNoError                   = 0,
    kAudioHardwareNotRunningError           = 'stop',
    kAudioHardwareUnspecifiedError          = 'what',
    kAudioHardwareUnknownPropertyError      = 'who?',
    kAudioHardwareBadPropertySizeError      = '!siz',
    kAudioHardwareIllegalOperationError     = 'nope',
    kAudioHardwareBadObjectError            = '!obj',
    kAudioHardwareBadDeviceError            = '!dev',
    kAudioHardwareBadStreamError            = '!str',
    kAudioHardwareUnsupportedOperationError = 'unop',
    kAudioDeviceUnsupportedFormatError      = '!dat',
    kAudioDevicePermissionsError            = '!hog'
};

/*!
    @enum           Predefined AudioObjectID values 
    @abstract       ObjectIDs that are always the same
    @constant       kAudioObjectUnknown
                        This is the sentinel value. No object will have an ID whose value is 0.
*/
enum
{
    kAudioObjectUnknown         = 0
};

/*!
    @enum           Property Address Constants
    @abstract       The valid values for the scope in a property address.
    @constant       kAudioObjectPropertyScopeGlobal
                        The AudioObjectPropertyScope for properties that apply to the object as a
                        whole. All objects have a global scope and for most it is their only scope.
    @constant       kAudioObjectPropertyScopeInput
                        The AudioObjectPropertyScope for properties that apply to the input side of
                        an object.
    @constant       kAudioObjectPropertyScopeOutput
                        The AudioObjectPropertyScope for properties that apply to the output side of
                        an object.
    @constant       kAudioObjectPropertyScopePlayThrough
                        The AudioObjectPropertyScope for properties that apply to the play through
                        side of an object.
    @constant       kAudioObjectPropertyElementMaster
                        The AudioObjectPropertyElement value for properties that apply to the master
                        element or to the entire scope.
*/
enum
{
    kAudioObjectPropertyScopeGlobal         = 'glob',
    kAudioObjectPropertyScopeInput          = 'inpt',
    kAudioObjectPropertyScopeOutput         = 'outp',
    kAudioObjectPropertyScopePlayThrough    = 'ptru',
    kAudioObjectPropertyElementMaster       = 0
};

/*!
    @enum           Wildcard Constants
    @abstract       Constants that are used as wildcards.
    @discussion     Wildcards match any and all values for thier associated type. They are useful
                    when registering to receive notificationss.
    @constant       kAudioObjectPropertySelectorWildcard
                        The wildcard value for AudioObjectPropertySelectors.
    @constant       kAudioObjectPropertyScopeWildcard
                        The wildcard value for AudioObjectPropertyScopes.
    @constant       kAudioObjectPropertyElementWildcard
                        The wildcard value for AudioObjectPropertyElements.
    @constant       kAudioObjectClassIDWildcard
                        The wildcard value for AudioClassIDs.
*/
enum
{
    kAudioObjectPropertySelectorWildcard    = '****',
    kAudioObjectPropertyScopeWildcard       = '****',
    kAudioObjectPropertyElementWildcard     = 0xFFFFFFFF,
    kAudioObjectClassIDWildcard             = '****'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioObject Constants

/*!
    @enum           AudioObject Class Constants
    @abstract       Various constants related to the AudioObject class.
    @discussion     The AudioObject class is the base class for all classes.
    @constant       kAudioObjectClassID
                        The AudioClassID that identifies the AudioObject class.
*/
enum
{
    kAudioObjectClassID = 'aobj'
};

//==================================================================================================
#pragma mark AudioObject Properties

/*!
    @enum           AudioObject Property Selectors
    @abstract       AudioObjectPropertySelector values provided by objects of the AudioObject class.
    @discussion     The AudioObject class is the base class for all classes. As such, all classes
                    inherit this set of properties.
    @constant       kAudioObjectPropertyBaseClass
                        An AudioClassID that identifies the class from which the clase of the
                        AudioObject is derived. This value must always be one of the standard
                        classes.
    @constant       kAudioObjectPropertyClass
                        An AudioClassID that identifies the class of the AudioObject.
    @constant       kAudioObjectPropertyOwner
                        An AudioObjectID that identifies the the AudioObject that owns the given
                        AudioObject. Note that all AudioObjects are owned by some other AudioObject.
                        The only exception is the AudioSystemObject, for which the value of this
                        property is kAudioObjectUnknown.
    @constant       kAudioObjectPropertyName
                        A CFString that contains the human readable name of the object. The caller
                        is responsible for releasing the returned CFObject.
    @constant       kAudioObjectPropertyModelName
                        A CFString that contains the human readable model name of the object. The
                        model name differs from kAudioObjectPropertyName in that two objects of the
                        same model will have the same value for this property but may have different
                        values for kAudioObjectPropertyName.
    @constant       kAudioObjectPropertyManufacturer
                        A CFString that contains the human readable name of the manufacturer of the
                        hardware the AudioObject is a part of. The caller is responsible for
                        releasing the returned CFObject.
    @constant       kAudioObjectPropertyElementName
                        A CFString that contains a human readable name for the given element in the
                        given scope. The caller is responsible for releasing the returned CFObject.
    @constant       kAudioObjectPropertyElementCategoryName
                        A CFString that contains a human readable name for the category of the given
                        element in the given scope. The caller is responsible for releasing the
                        returned CFObject.
    @constant       kAudioObjectPropertyElementNumberName
                        A CFString that contains a human readable name for the number of the given
                        element in the given scope. The caller is responsible for releasing the
                        returned CFObject.
    @constant       kAudioObjectPropertyOwnedObjects
                        An array of AudioObjectIDs that represent all the AudioObjects owned by the
                        given object. The qualifier is an array of AudioClassIDs. If it is
                        non-empty, the returned array of AudioObjectIDs will only refer to objects
                        whose class is in the qualifier array or whose is a subclass of one in the
                        qualifier array.
*/
enum
{
    kAudioObjectPropertyBaseClass           = 'bcls',
    kAudioObjectPropertyClass               = 'clas',
    kAudioObjectPropertyOwner               = 'stdv',
    kAudioObjectPropertyName                = 'lnam',
    kAudioObjectPropertyModelName           = 'lmod',
    kAudioObjectPropertyManufacturer        = 'lmak',
    kAudioObjectPropertyElementName         = 'lchn',
    kAudioObjectPropertyElementCategoryName = 'lccn',
    kAudioObjectPropertyElementNumberName   = 'lcnn',
    kAudioObjectPropertyOwnedObjects        = 'ownd'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioPlugIn Constants

/*!
    @enum           AudioPlugIn Class Constants
    @abstract       Various constants related to the AudioPlugIn class.
    @constant       kAudioPlugInClassID
                        The AudioClassID that identifies the AudioPlugIn class.
*/
enum
{
    kAudioPlugInClassID = 'aplg'
};

//==================================================================================================
#pragma mark AudioPlugIn Properties

/*!
    @enum           AudioPlugIn Properties
    @abstract       AudioObjectPropertySelector values provided by the AudioPlugIn class.
    @discussion     The AudioPlugIn class is a subclass of the AudioObject class. The class has just
                    the global scope, kAudioObjectPropertyScopeGlobal, and only a master element.
    @constant       kAudioPlugInPropertyBundleID
                        A CFString that contains the bundle identifier for the AudioPlugIn. The
                        caller is responsible for releasing the returned CFObject.
    @constant       kAudioPlugInPropertyDeviceList
                        An array of AudioObjectIDs that represent all the AudioDevices currently
                        provided by the plug-in.
    @constant       kAudioPlugInPropertyTranslateUIDToDevice
                        This property fetches the AudioObjectID that corresponds to the AudioDevice
                        that has the given UID. The UID is passed in via the qualifier as a CFString
                        while the AudioObjectID for the AudioDevice is returned to the caller as the
                        property's data. Note that an error is not returned if the UID doesn't refer
                        to any AudioDevices. Rather, this property will return kAudioObjectUnknown
                        as the value of the property.
*/
enum
{
    kAudioPlugInPropertyBundleID                = 'piid',
    kAudioPlugInPropertyDeviceList              = 'dev#',
    kAudioPlugInPropertyTranslateUIDToDevice    = 'uidd'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioTransportManager Constants

/*!
    @enum           AudioTransportManager Class Constants
    @abstract       Various constants related to the AudioTransportManager class.
    @discussion     The AudioTransportManager class is a subclass of the AudioPlugIn class.
                    Instances manage an entire tranport mechanism such as AirPlay or an AVB network
                    of devices. AudioTransportManagers present a list of AudioEndPoints that
                    represent all the devices that they manage. They can combine AudioEndPoints into
                    an AudioEndPointDevice that can be used by the system the same as any other
                    AudioDevice.
    @constant       kAudioTransportManagerClassID
                        The AudioClassID that identifies the AudioTransportManager class.
*/
enum
{
    kAudioTransportManagerClassID   = 'trpm'
};

//==================================================================================================
#pragma mark AudioTransportManager Properties

/*!
    @enum           AudioTransportManager Properties
    @abstract       AudioObjectPropertySelector values provided by the AudioTransportManager class.
    @discussion     The AudioTransportManager class is a subclass of the AudioPlugIn class. The
                    class has just the global scope, kAudioObjectPropertyScopeGlobal, and only a
                    master element.
    @constant       kAudioTransportManagerPropertyEndPointList
                        An array of AudioObjectIDs for all the AudioEndPoint objects the transport
                        manager is tracking.
    @constant       kAudioTransportManagerPropertyTranslateUIDToEndPoint
                        This property fetches the AudioObjectID that corresponds to the
                        AudioEndpoint that has the given UID. The UID is passed in via the qualifier
                        as a CFString while the AudioObjectID for the AudioEndpoint is returned to
                        the caller as the property's data. Note that an error is not returned if the
                        UID doesn't refer to any AudioEndpoints. Rather, this property will return
                        kAudioObjectUnknown as the value of the property.
    @constant       kAudioTransportManagerPorpertyTransportType
                        A UInt32 whose value indicates how the transport manager's endpoints and 
						endpoint devices are connected to the CPU. Constants for some of the values
						for this property can be found in the enum in the AudioDevice Constants
						section of this file.
*/
enum
{
    kAudioTransportManagerPropertyEndPointList              = 'end#',
    kAudioTransportManagerPropertyTranslateUIDToEndPoint    = 'uide',
	kAudioTransportManagerPropertyTransportType				= 'tran'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioDevice Constants

/*!
    @enum           AudioDevice Class Constants
    @abstract       Various constants related to the AudioDevice class.
    @constant       kAudioDeviceClassID
                        The AudioClassID that identifies the AudioDevice class.
*/
enum
{
    kAudioDeviceClassID = 'adev'
};

/*!
    @enum           Transport Type IDs
    @abstract       Commonly used values for kAudioDevicePropertyTransportType and
					kAudioTransportManagerPropertyTransportType
    @constant       kAudioDeviceTransportTypeUnknown
                        The transport type ID returned when a device doesn't provide a transport
                        type.
    @constant       kAudioDeviceTransportTypeBuiltIn
                        The transport type ID for AudioDevices built into the system.
    @constant       kAudioDeviceTransportTypeAggregate
                        The transport type ID for aggregate devices.
    @constant       kAudioDeviceTransportTypeAutoAggregate
                        The transport type ID for automatically generated aggregate devices.
    @constant       kAudioDeviceTransportTypeVirtual
                        The transport type ID for AudioDevices that don't correspond to real audio
                        hardware.
    @constant       kAudioDeviceTransportTypePCI
                        The transport type ID for AudioDevices connected via the PCI bus.
    @constant       kAudioDeviceTransportTypeUSB
                        The transport type ID for AudioDevices connected via USB.
    @constant       kAudioDeviceTransportTypeFireWire
                        The transport type ID for AudioDevices connected via FireWire.
    @constant       kAudioDeviceTransportTypeBluetooth
                        The transport type ID for AudioDevices connected via Bluetooth.
    @constant       kAudioDeviceTransportTypeHDMI
                        The transport type ID for AudioDevices connected via HDMI.
    @constant       kAudioDeviceTransportTypeDisplayPort
                        The transport type ID for AudioDevices connected via DisplayPort.
    @constant       kAudioDeviceTransportTypeAirPlay
                        The transport type ID for AudioDevices connected via AirPlay.
    @constant       kAudioDeviceTransportTypeAVB
                        The transport type ID for AudioDevices connected via AVB.
    @constant       kAudioDeviceTransportTypeThunderbolt
                        The transport type ID for AudioDevices connected via Thunderbolt.
*/
enum
{
    kAudioDeviceTransportTypeUnknown        = 0,
    kAudioDeviceTransportTypeBuiltIn        = 'bltn',
    kAudioDeviceTransportTypeAggregate      = 'grup',
    kAudioDeviceTransportTypeAutoAggregate  = 'fgrp',
    kAudioDeviceTransportTypeVirtual        = 'virt',
    kAudioDeviceTransportTypePCI            = 'pci ',
    kAudioDeviceTransportTypeUSB            = 'usb ',
    kAudioDeviceTransportTypeFireWire       = '1394',
    kAudioDeviceTransportTypeBluetooth      = 'blue',
    kAudioDeviceTransportTypeHDMI           = 'hdmi',
    kAudioDeviceTransportTypeDisplayPort    = 'dprt',
    kAudioDeviceTransportTypeAirPlay        = 'airp',
    kAudioDeviceTransportTypeAVB            = 'eavb',
    kAudioDeviceTransportTypeThunderbolt    = 'thun'
};

//==================================================================================================
#pragma mark AudioDevice Properties

/*!
    @enum           AudioDevice Properties
    @abstract       AudioObjectPropertySelector values provided by the AudioDevice class.
    @discussion     The AudioDevice class is a subclass of the AudioObjectClass. The class has four
                    scopes, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyScopeInput,
                    kAudioObjectPropertyScopeOutput, and kAudioObjectPropertyScopePlayThrough. The
                    class has a master element and an element for each channel in each stream
                    numbered according to the starting channel number of each stream.
    @constant       kAudioDevicePropertyConfigurationApplication
                        A CFString that contains the bundle ID for an application that provides a
                        GUI for configuring the AudioDevice. By default, the value of this property
                        is the bundle ID for Audio MIDI Setup. The caller is responsible for
                        releasing the returned CFObject.
    @constant       kAudioDevicePropertyDeviceUID
                        A CFString that contains a persistent identifier for the AudioDevice. An
                        AudioDevice's UID is persistent across boots. The content of the UID string
                        is a black box and may contain information that is unique to a particular
                        instance of an AudioDevice's hardware or unique to the CPU. Therefore they
                        are not suitable for passing between CPUs or for identifying similar models
                        of hardware. The caller is responsible for releasing the returned CFObject.
    @constant       kAudioDevicePropertyModelUID
                        A CFString that contains a persistent identifier for the model of an
                        AudioDevice. The identifier is unique such that the identifier from two
                        AudioDevices are equal if and only if the two AudioDevices are the exact
                        same model from the same manufacturer. Further, the identifier has to be the
                        same no matter on what machine the AudioDevice appears. The caller is
                        responsible for releasing the returned CFObject.
    @constant       kAudioDevicePropertyTransportType
                        A UInt32 whose value indicates how the AudioDevice is connected to the CPU.
                        Constants for some of the values for this property can be found in the enum
                        in the AudioDevice Constants section of this file.
    @constant       kAudioDevicePropertyRelatedDevices
                        An array of AudioDeviceIDs for devices related to the AudioDevice. For
                        IOAudio-based devices, a AudioDevices are related if they share the same
                        IOAudioDevice object.
    @constant       kAudioDevicePropertyClockDomain
                        A UInt32 whose value indicates the clock domain to which this AudioDevice
                        belongs. AudioDevices that have the same value for this property are able to
                        be synchronized in hardware. However, a value of 0 indicates that the clock
                        domain for the device is unspecified and should be assumed to be separate
                        from every other device's clock domain, even if they have the value of 0 as
                        their clock domain as well.
    @constant       kAudioDevicePropertyDeviceIsAlive
                        A UInt32 where a value of 1 means the device is ready and available and 0
                        means the device is usable and will most likely go away shortly.
    @constant       kAudioDevicePropertyDeviceIsRunning
                        A UInt32 where a value of 0 means the AudioDevice is not performing IO and
                        a value of 1 means that it is. Note that the device can be running even if
                        there are no active IOProcs such as by calling AudioDeviceStart() and
                        passing a NULL IOProc. Note that the notification for this property is
                        usually sent from the AudioDevice's IO thread.
    @constant       kAudioDevicePropertyDeviceCanBeDefaultDevice
                        A UInt32 where 1 means that the AudioDevice is a possible selection for
                        kAudioHardwarePropertyDefaultInputDevice or
                        kAudioHardwarePropertyDefaultOutputDevice depending on the scope.
    @constant       kAudioDevicePropertyDeviceCanBeDefaultSystemDevice
                        A UInt32 where 1 means that the AudioDevice is a possible selection for
                        kAudioHardwarePropertyDefaultSystemOutputDevice.
    @constant       kAudioDevicePropertyLatency
                        A UInt32 containing the number of frames of latency in the AudioDevice. Note
                        that input and output latency may differ. Further, the AudioDevice's
                        AudioStreams may have additional latency so they should be queried as well.
                        If both the device and the stream say they have latency, then the total
                        latency for the stream is the device latency summed with the stream latency.
    @constant       kAudioDevicePropertyStreams
                        An array of AudioStreamIDs that represent the AudioStreams of the
                        AudioDevice. Note that if a notification is received for this property, any
                        cached AudioStreamIDs for the device become invalid and need to be
                        re-fetched.
    @constant       kAudioObjectPropertyControlList
                        An array of AudioObjectIDs that represent the AudioControls of the
                        AudioDevice. Note that if a notification is received for this property, any
                        cached AudioObjectIDs for the device become invalid and need to be
                        re-fetched.
    @constant       kAudioDevicePropertySafetyOffset
                        A UInt32 whose value indicates the number for frames in ahead (for output)
                        or behind (for input the current hardware position that is safe to do IO.
    @constant       kAudioDevicePropertyNominalSampleRate
                        A Float64 that indicates the current nominal sample rate of the AudioDevice.
    @constant       kAudioDevicePropertyAvailableNominalSampleRates
                        An array of AudioValueRange structs that indicates the valid ranges for the
                        nominal sample rate of the AudioDevice.
    @constant       kAudioDevicePropertyIcon
                        A CFURLRef that indicates an image file that can be used to represent the
                        device visually. The caller is responsible for releasing the returned
                        CFObject.
    @constant       kAudioDevicePropertyIsHidden
                        A UInt32 where a non-zero value indicates that the device is not included
                        in the normal list of devices provided by kAudioHardwarePropertyDevices nor
                        can it be the default device. Hidden devices can only be discovered by
                        knowing their UID and using kAudioHardwarePropertyDeviceForUID.
    @constant       kAudioDevicePropertyPreferredChannelsForStereo
                        An array of two UInt32s, the first for the left channel, the second for the
                        right channel, that indicate the channel numbers to use for stereo IO on the
                        device. The value of this property can be different for input and output and
                        there are no restrictions on the channel numbers that can be used.
    @constant       kAudioDevicePropertyPreferredChannelLayout
                        An AudioChannelLayout that indicates how each channel of the AudioDevice
                        should be used.
*/
enum
{
    kAudioDevicePropertyConfigurationApplication        = 'capp',
    kAudioDevicePropertyDeviceUID                       = 'uid ',
    kAudioDevicePropertyModelUID                        = 'muid',
    kAudioDevicePropertyTransportType                   = 'tran',
    kAudioDevicePropertyRelatedDevices                  = 'akin',
    kAudioDevicePropertyClockDomain                     = 'clkd',
    kAudioDevicePropertyDeviceIsAlive                   = 'livn',
    kAudioDevicePropertyDeviceIsRunning                 = 'goin',
    kAudioDevicePropertyDeviceCanBeDefaultDevice        = 'dflt',
    kAudioDevicePropertyDeviceCanBeDefaultSystemDevice  = 'sflt',
    kAudioDevicePropertyLatency                         = 'ltnc',
    kAudioDevicePropertyStreams                         = 'stm#',
    kAudioObjectPropertyControlList                     = 'ctrl',
    kAudioDevicePropertySafetyOffset                    = 'saft',
    kAudioDevicePropertyNominalSampleRate               = 'nsrt',
    kAudioDevicePropertyAvailableNominalSampleRates     = 'nsr#',
    kAudioDevicePropertyIcon                            = 'icon',
    kAudioDevicePropertyIsHidden                        = 'hidn',
    kAudioDevicePropertyPreferredChannelsForStereo      = 'dch2',
    kAudioDevicePropertyPreferredChannelLayout          = 'srnd'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioEndPointDevice Constants

/*!
    @enum           AudioEndPointDevice Class Constants
    @abstract       Various constants related to the AudioEndPointDevice class.
    @constant       kAudioEndPointDeviceClassID
                        The AudioClassID that identifies the AudioEndPointDevice class.
*/
enum
{
    kAudioEndPointDeviceClassID = 'edev'
};

/*!
    @defined        kAudioEndPointDeviceUIDKey
    @discussion     The key used in a CFDictionary that describes the composition of an
                    AudioEndPointDevice. The value for this key is a CFString that contains the UID
                    of the AudioEndPointDevice.
*/
#define kAudioEndPointDeviceUIDKey  "uid"

/*!
    @defined        kAudioEndPointDeviceNameKey
    @discussion     The key used in a CFDictionary that describes the composition of an
                    AudioEndPointDevice. The value for this key is a CFString that contains the
                    human readable name of the AudioEndPointDevice.
*/
#define kAudioEndPointDeviceNameKey "name"

/*!
    @defined        kAudioEndPointDeviceEndPointListKey
    @discussion     The key used in a CFDictionary that describes the composition of an
                    AudioEndPointDevice. The value for this key is a CFArray of CFDictionaries that
                    describe each AudioEndPoint in the AudioEndPointDevice. The keys for this
                    CFDictionary are defined in the AudioEndPoint Constants section.
*/
#define kAudioEndPointDeviceEndPointListKey "endpoints"

/*!
    @defined        kAudioEndPointDeviceMasterEndPointKey
    @discussion     The key used in a CFDictionary that describes the composition of an
                    AudioEndPointDevice. The value for this key is a CFString that contains the UID
                    for the AudioEndPoint that is the master time source for the
                    AudioEndPointDevice.
*/
#define kAudioEndPointDeviceMasterEndPointKey   "master"

/*!
    @defined        kAudioEndPointDeviceIsPrivateKey
    @discussion     The key used in a CFDictionary that describes the composition of an
                    AudioEndPointDevice. The value for this key is a CFNumber where a value of 0
                    means that the AudioEndPointDevice is to be published to the entire system and a
                    value of 1 means that the AudioEndPointDevice is private to the process that
                    created it. Note that a private AudioEndPointDevice is not persistent across
                    launches of the process that created it. Note that if this key is not present,
                    it implies that the AudioEndPointDevice is published to the entire system.
*/
#define kAudioEndPointDeviceIsPrivateKey    "private"

//==================================================================================================
#pragma mark AudioEndPointDevice Properties

/*!
    @enum           AudioEndPointDevice Properties
    @abstract       AudioObjectPropertySelector values provided by the AudioEndPointDevice class.
    @discussion     AudioEndPointDevice is a subclass of AudioDevice and has the same scope and
                    element structure.
    @constant       kAudioEndPointDevicePropertyComposition
                        A CFDictionary that describes the composition of the AudioEndPointDevice.
                        The keys for this CFDicitionary are defined in the AudioEndPointDevice
                        Constants section. The caller is responsible for releasing the returned
                        CFObject.
    @constant       kAudioEndPointDevicePropertyEndPointList
                        An array of AudioObjectIDs for all the AudioEndPoints in the device.
    @constant       kAudioEndPointDevicePropertyIsPrivate
                        A pid_t where a value of 0 idicates that the device is public and a non-zero
                        value indicates the pid of the process that owns the device.
*/
enum
{
    kAudioEndPointDevicePropertyComposition         = 'acom',
    kAudioEndPointDevicePropertyEndPointList        = 'agrp',
    kAudioEndPointDevicePropertyIsPrivate           = 'priv'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioEndPoint Constants

/*!
    @enum           AudioEndPoint Class Constants
    @abstract       Various constants related to the AudioEndPoint class.
    @discussion     The AudioEndPoint class is a subclass of AudioDevice class and has the same
                    scope and element structure. However, AudioEndPoint objects do not implement an
                    IO path of their own and as such do not implmenent any  AudioDevice properties
                    associated with the IO path.
    @constant       kAudioEndPointDeviceClassID
                        The AudioClassID that identifies the AudioEndPointDevice class.
*/
enum
{
    kAudioEndPointClassID   = 'endp'
};

/*!
    @defined        kAudioEndPointUIDKey
    @discussion     The key used in a CFDictionary that describes the state of an AudioEndPoint in a
                    description dictionary for an AudioEndPointDevice. The value for this key is a
                    CFString that contains the UID for the AudioEndPoint.
*/
#define kAudioEndPointUIDKey    "uid"

/*!
    @defined        kAudioEndPointNameKey
    @discussion     The key used in a CFDictionary that describes the state of an AudioEndPoint in a
                    description dictionary for an AudioEndPointDevice. The value for this key is a
                    CFString that contains the human readable name of the AudioEndPoint.
*/
#define kAudioEndPointNameKey   "name"

/*!
    @defined        kAudioEndPointInputChannelsKey
    @discussion     The key used in a CFDictionary that describes the state of an AudioEndPoint in a
                    description dictionary for an AudioEndPointDevice. The value for this key is a
                    CFNumber that indicates the total number of input channels for the
                    AudioEndPoint.
*/
#define kAudioEndPointInputChannelsKey  "channels-in"

/*!
    @defined        kAudioEndPointOutputChannelsKey
    @discussion     The key used in a CFDictionary that describes the state of an AudioEndPoint in a
                    description dictionary for an AudioEndPointDevice. The value for this key is a
                    CFNumber that indicates the total number of output channels for the
                    AudioEndPoint.
*/
#define kAudioEndPointOutputChannelsKey "channels-out"

//==================================================================================================
#pragma mark -
#pragma mark AudioStream Types

/*!
    @struct         AudioStreamRangedDescription
    @abstract       This structure allows a specific sample rate range to be associated with an
                    AudioStreamBasicDescription that specifies it's sample rate as
                    kAudioStreamAnyRate.
    @discussion     Note that this structure is only used to desicribe the the available formats
                    for a stream. It is not used for the current format.
    @field          mFormat
                        The AudioStreamBasicDescription that describes the format of the stream.
                        Note that the mSampleRate field of the structure will be the same as the
                        the values in mSampleRateRange when only a single sample rate is supported.
                        It will be kAudioStreamAnyRate when there is a range with more elements. 
    @field          mSampleRateRange
                        The AudioValueRange that describes the minimum and maximum sample rate for
                        the stream. If the mSampleRate field of mFormat is kAudioStreamAnyRate the
                        format supports the range of sample rates described by this structure.
                        Otherwise, the minimum will be the same as the maximum which will be the
                        same as the mSampleRate field of mFormat.
*/
struct  AudioStreamRangedDescription
{
    AudioStreamBasicDescription     mFormat;
    AudioValueRange                 mSampleRateRange;
};
typedef struct AudioStreamRangedDescription AudioStreamRangedDescription;

//==================================================================================================
#pragma mark AudioStream Constants

/*!
    @enum           AudioStream Class Constants
    @abstract       Various constants related to the AudioStream class.
    @constant       kAudioStreamClassID
                        The AudioClassID that identifies the AudioStream class.
*/
enum
{
    kAudioStreamClassID = 'astr'
};

/*!
    @enum           AudioStream Terminal Types
    @abstract       Various constants that describe the terminal type of an AudioStream.
    @constant       kAudioStreamTerminalTypeUnknown
                        The ID used when the terminal type for the AudioStream is non known.
    @constant       kAudioStreamTerminalTypeLine
                        The ID for a terminal type of a line level stream. Note that this applies to
                        both input streams and output streams
    @constant       kAudioStreamTerminalTypeDigitalAudioInterface
                        The ID for a terminal type of stream from/to a digital audio interface as
                        defined by ISO 60958 (aka SPDIF or AES/EBU). Note that this applies to both
                        input streams and output streams
    @constant       kAudioStreamTerminalTypeSpeaker
                        The ID for a terminal type of a speaker.
    @constant       kAudioStreamTerminalTypeHeadphones
                        The ID for a terminal type of headphones.
    @constant       kAudioStreamTerminalTypeLFESpeaker
                        The ID for a terminal type of a speaker for low frequency effects.
    @constant       kAudioStreamTerminalTypeReceiverSpeaker
                        The ID for a terminal type of a speaker on a telephone handset receiver.
    @constant       kAudioStreamTerminalTypeMicrophone
                        The ID for a terminal type of a microphone.
    @constant       kAudioStreamTerminalTypeHeadsetMicrophone
                        The ID for a terminal type of a microphone attached to an headset.
    @constant       kAudioStreamTerminalTypeReceiverMicrophone
                        The ID for a terminal type of a microhpone on a telephone handset recevier.
    @constant       kAudioStreamTerminalTypeTTY
                        The ID for a terminal type of a device providing a TTY signal.
    @constant       kAudioStreamTerminalTypeHDMI
                        The ID for a terminal type of a stream from/to an HDMI port.
    @constant       kAudioStreamTerminalTypeDisplayPort
                        The ID for a terminal type of a stream from/to an DisplayPort port.
*/
enum
{
    kAudioStreamTerminalTypeUnknown                 = 0,
    kAudioStreamTerminalTypeLine                    = 'line',
    kAudioStreamTerminalTypeDigitalAudioInterface   = 'spdf',
    kAudioStreamTerminalTypeSpeaker                 = 'spkr',
    kAudioStreamTerminalTypeHeadphones              = 'hdph',
    kAudioStreamTerminalTypeLFESpeaker              = 'lfes',
    kAudioStreamTerminalTypeReceiverSpeaker         = 'rspk',
    kAudioStreamTerminalTypeMicrophone              = 'micr',
    kAudioStreamTerminalTypeHeadsetMicrophone       = 'hmic',
    kAudioStreamTerminalTypeReceiverMicrophone      = 'rmic',
    kAudioStreamTerminalTypeTTY                     = 'tty_',
    kAudioStreamTerminalTypeHDMI                    = 'hdmi',
    kAudioStreamTerminalTypeDisplayPort             = 'dprt'
};

//==================================================================================================
#pragma mark AudioStream Properties

/*!
    @enum           AudioStream Properties
    @abstract       AudioObjectPropertySelector values provided by the AudioStream class.
    @discussion     AudioStream is a subclass of AudioObject and has only the single scope,
                    kAudioObjectPropertyScopeGlobal. They have a master element and an element for
                    each channel in the stream numbered upward from 1.
    @constant       kAudioStreamPropertyIsActive
                        A UInt32 where a non-zero value indicates that the stream is enabled and
                        doing IO.
    @constant       kAudioStreamPropertyDirection
                        A UInt32 where a value of 0 means that this AudioStream is an output stream
                        and a value of 1 means that it is an input stream.
    @constant       kAudioStreamPropertyTerminalType
                        A UInt32 whose value describes the general kind of functionality attached
                        to the AudioStream.
    @constant       kAudioStreamPropertyStartingChannel
                        A UInt32 that specifies the first element in the owning device that
                        corresponds to element one of this stream.
    @constant       kAudioStreamPropertyLatency
                        A UInt32 containing the number of frames of latency in the AudioStream. Note
                        that the owning AudioDevice may have additional latency so it should be
                        queried as well. If both the device and the stream say they have latency,
                        then the total latency for the stream is the device latency summed with the
                        stream latency.
    @constant       kAudioStreamPropertyVirtualFormat
                        An AudioStreamBasicDescription that describes the current data format for
                        the AudioStream. The virtual format refers to the data format in which all
                        IOProcs for the owning AudioDevice will perform IO transactions.
    @constant       kAudioStreamPropertyAvailableVirtualFormats
                        An array of AudioStreamRangedDescriptions that describe the available data
                        formats for the AudioStream. The virtual format refers to the data format in
                        which all IOProcs for the owning AudioDevice will perform IO transactions.
    @constant       kAudioStreamPropertyPhysicalFormat
                        An AudioStreamBasicDescription that describes the current data format for
                        the AudioStream. The physical format refers to the data format in which the
                        hardware for the owning AudioDevice performs it's IO transactions.
    @constant       kAudioStreamPropertyAvailablePhysicalFormats
                        An array of AudioStreamRangedDescriptions that describe the available data
                        formats for the AudioStream. The physical format refers to the data format
                        in which the hardware for the owning AudioDevice performs it's IO
                        transactions.
*/
enum
{
    kAudioStreamPropertyIsActive                    = 'sact',
    kAudioStreamPropertyDirection                   = 'sdir',
    kAudioStreamPropertyTerminalType                = 'term',
    kAudioStreamPropertyStartingChannel             = 'schn',
    kAudioStreamPropertyLatency                     = kAudioDevicePropertyLatency,
    kAudioStreamPropertyVirtualFormat               = 'sfmt',
    kAudioStreamPropertyAvailableVirtualFormats     = 'sfma',
    kAudioStreamPropertyPhysicalFormat              = 'pft ',
    kAudioStreamPropertyAvailablePhysicalFormats    = 'pfta'
};
//==================================================================================================
#pragma mark -
#pragma mark AudioControl Constants

/*!
    @enum           AudioControl Class Constants
    @abstract       Various constants related to the AudioControl class.
    @constant       kAudioControlClassID
                        The AudioClassID that identifies the AudioControl class.
*/
enum
{
    kAudioControlClassID    = 'actl'
};

/*!
    @enum           AudioControl Property Selectors
    @abstract       AudioObjectPropertySelector values provided by the AudioControl class.
    @discussion     The AudioControl class is a subclass of the AudioObject class. The class has
                    just the global scope, kAudioObjectPropertyScopeGlobal, and only a master
                    element.
    @constant       kAudioControlPropertyScope
                        An AudioServerPlugIn_PropertyScope that indicates which part of a device the
                        control applies to.
    @constant       kAudioControlPropertyElement
                        An AudioServerPlugIn_PropertyElement that indicates which element of the
                        device the control applies to.
*/
enum
{
    kAudioControlPropertyScope      = 'cscp',
    kAudioControlPropertyElement    = 'celm'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioSliderControl Constants

/*!
    @enum           AudioSliderControl Class Constants
    @abstract       Various constants related to the AudioSliderControl class.
    @constant       kAudioSliderControlClassID
                        The AudioClassID that identifies the AudioSliderControl class.
*/
enum
{
    kAudioSliderControlClassID  = 'sldr'
};

/*!
    @enum           AudioSliderControl Property Selectors
    @abstract       AudioObjectPropertySelector values provided by the AudioSliderControl class.
    @discussion     The AudioSliderControl class is a subclass of the AudioControl class and has the
                    same scope and element structure.
    @constant       kAudioSliderControlPropertyValue
                        A UInt32 that represents the value of the slider control.
    @constant       kAudioSliderControlPropertyRange
                        An array of two UInt32s that represents the inclusive range of values the
                        slider control can take.
*/
enum
{
    kAudioSliderControlPropertyValue    = 'sdrv',
    kAudioSliderControlPropertyRange    = 'sdrr'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioLevelControl Constants

/*!
    @enum           AudioLevelControl Class Constants
    @abstract       Various constants related to the AudioLevelControl class.
    @constant       kAudioLevelControlClassID
                        The AudioClassID that identifies the LevelControl class.
    @constant       kAudioVolumeControlClassID
                        A subclass of the LevelControl class that implements a general
                        gain/attenuation stage.
    @constant       kAudioLFEVolumeControlClassID
                        A subclass of the LevelControl class for an LFE channel that results from
                        bass management. Note that LFE channels that are represented as normal audio
                        channels must use kAudioVolumeControlClassID to manipulate the level.
*/
enum
{
    kAudioLevelControlClassID       = 'levl',
    kAudioVolumeControlClassID      = 'vlme',
    kAudioLFEVolumeControlClassID   = 'subv'
};

/*!
    @enum           AudioLevelControl Property Selectors
    @abstract       AudioObjectPropertySelector values provided by the AudioLevelControl class.
    @discussion     The AudioLevelControl class is a subclass of the AudioControl class and has the
                    same scope and element structure.
    @constant       kAudioLevelControlPropertyScalarValue
                        A Float32 that represents the value of the volume control. The range is
                        between 0.0 and 1.0 (inclusive). Note that the set of all Float32 values
                        between 0.0 and 1.0 inclusive is much larger than the set of actual values
                        that the hardware can select. This means that the Float32 range has a many
                        to one mapping with the underlying hardware values. As such, setting a
                        scalar value will result in the control taking on the value nearest to what
                        was set.
    @constant       kAudioLevelControlPropertyDecibelValue
                        A Float32 that represents the value of the volume control in dB. Note that
                        the set of all Float32 values in the dB range for the control is much larger
                        than the set of actual values that the hardware can select. This means that
                        the Float32 range has a many to one mapping with the underlying hardware
                        values. As such, setting a dB value will result in the control taking on the
                        value nearest to what was set.
    @constant       kAudioLevelControlPropertyDecibelRange
                        An AudioValueRange that contains the minimum and maximum dB values the
                        control can have.
    @constant       kAudioLevelControlPropertyConvertScalarToDecibels
                        A Float32 that on input contains a scalar volume value for the and on exit
                        contains the equivalent dB value.
    @constant       kAudioLevelControlPropertyConvertDecibelsToScalar
                        A Float32 that on input contains a dB volume value for the and on exit
                        contains the equivalent scalar value.
*/
enum
{
    kAudioLevelControlPropertyScalarValue               = 'lcsv',
    kAudioLevelControlPropertyDecibelValue              = 'lcdv',
    kAudioLevelControlPropertyDecibelRange              = 'lcdr',
    kAudioLevelControlPropertyConvertScalarToDecibels   = 'lcsd',
    kAudioLevelControlPropertyConvertDecibelsToScalar   = 'lcds'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioBooleanControl Constants

/*!
    @enum           AudioBooleanControl Class Constants
    @abstract       Various constants related to the AudioBooleanControl class.
    @constant       kAudioBooleanControlClassID
                        The AudioClassID that identifies the BooleanControl class.
    @constant       kAudioMuteControlClassID
                        A subclass of the AudioBooleanControl class where a true value means that
                        mute is enabled making that element inaudible.
    @constant       kAudioSoloControlClassID
                        A subclass of the AudioBooleanControl class where a true value means that
                        solo is enabled making just that element audible and the other elements
                        inaudible.
    @constant       kAudioJackControlClassID
                        A subclass of the AudioBooleanControl class where a true value means
                        something is plugged into that element.
    @constant       kAudioLFEMuteControlClassID
                        A subclass of the AudioBooleanControl class where true means that mute is
                        enabled making that LFE element inaudible. This control is for LFE channels
                        that result from bass management. Note that LFE channels that are
                        represented as normal audio channels must use an AudioMuteControl.
    @constant       kAudioPhantomPowerControlClassID
                        A subclass of the AudioBooleanControl class where true means that the
                        element's hardware has phantom power enabled.
    @constant       kAudioPhaseInvertControlClassID
                        A subclass of the AudioBooleanControl class where true means that the phase
                        of the signal on the given element is being inverted by 180 degrees.
    @constant       kAudioClipLightControlClassID
                        A subclass of the AudioBooleanControl class where true means that the signal
                        for the element has exceeded the sample range. Once a clip light is turned
                        on, it is to stay on until either the value of the control is set to false
                        or the current IO session stops and a new IO session starts.
    @constant       kAudioTalkbackControlClassID
                        An AudioBooleanControl where true means that the talkback channel is
                        enabled. This control is for talkback channels that are handled outside of 
                        the regular IO channels. If the talkback channel is among the normal IO
                        channels, it will use AudioMuteControl.
    @constant       kAudioListenbackControlClassID
                        An AudioBooleanControl where true means that the listenback channel is
                        audible. This control is for listenback channels that are handled outside of 
                        the regular IO channels. If the listenback channel is among the normal IO
                        channels, it will use AudioMuteControl.
*/
enum
{
    kAudioBooleanControlClassID         = 'togl',
    kAudioMuteControlClassID            = 'mute',
    kAudioSoloControlClassID            = 'solo',
    kAudioJackControlClassID            = 'jack',
    kAudioLFEMuteControlClassID         = 'subm',
    kAudioPhantomPowerControlClassID    = 'phan',
    kAudioPhaseInvertControlClassID     = 'phsi',
    kAudioClipLightControlClassID       = 'clip',
    kAudioTalkbackControlClassID        = 'talb',
    kAudioListenbackControlClassID      = 'lsnb'
};

/*!
    @enum           AudioBooleanControl Property Selectors
    @abstract       AudioObjectPropertySelector values provided by the AudioBooleanControl class.
    @discussion     The AudioBooleanControl class is a subclass of the AudioControl class and has
                    the same scope and element structure.
    @constant       kAudioBooleanControlPropertyValue
                        A UInt32 where 0 means off/false and non-zero means on/true.
*/
enum
{
    kAudioBooleanControlPropertyValue   = 'bcvl'
};

//==================================================================================================
#pragma mark -
#pragma mark AudioSelectorControl Constants

/*!
    @enum           AudioSelectorControl Class Constants
    @abstract       Various constants related to the AudioSelectorControl class.
    @constant       kAudioSelectorControlClassID
                        The AudioClassID that identifies the AudioSelectorControl class.
    @constant       kAudioDataSourceControlClassID
                        A subclass of the AudioSelectorControl class that identifies where the data
                        for the element is coming from.
    @constant       kAudioDataDestinationControlClassID
                        A subclass of the AudioSelectorControl class that identifies where the data
                        for the element is going.
    @constant       kAudioClockSourceControlClassID
                        A subclass of the AudioSelectorControl class that identifies where the
                        timing info for the object is coming from.
    @constant       kAudioLineLevelControlClassID
                        A subclass of the AudioSelectorControl class that identifies the nominal
                        line level for the element. Note that this is not a gain stage but rather
                        indicating the voltage standard (if any) used for the element, such as
                        +4dBu, -10dBV, instrument, etc.
    @constant       kAudioHighPassFilterControlClassID
                        A subclass of the AudioSelectorControl class that indicates the setting for
                        the high pass filter on the given element.
*/
enum
{
    kAudioSelectorControlClassID        = 'slct',
    kAudioDataSourceControlClassID      = 'dsrc',
    kAudioDataDestinationControlClassID = 'dest',
    kAudioClockSourceControlClassID     = 'clck',
    kAudioLineLevelControlClassID       = 'nlvl',
    kAudioHighPassFilterControlClassID  = 'hipf'
};

/*!
    @enum           AudioSelectorControl Property Selectors
    @abstract       AudioObjectPropertySelector values provided by the AudioSelectorControl class.
    @discussion     The AudioSelectorControl class is a subclass of the AudioControl class and has
                    the same scope and element structure.
    @constant       kAudioSelectorControlPropertyCurrentItem
                        An array of UInt32s that are the IDs of the items currently selected.
    @constant       kAudioSelectorControlPropertyAvailableItems
                        An array of UInt32s that represent the IDs of all the items available.
    @constant       kAudioSelectorControlPropertyItemName
                        This property translates the given item ID into a human readable name. The
                        qualifier contains the ID of the item to be translated and name is returned
                        as a CFString as the property data. The caller is responsible for releasing
                        the returned CFObject.
    @constant       kAudioSelectorControlPropertyItemKind
                        This property returns a UInt32 that identifies the kind of selector item the
                        item ID refers to. The qualifier contains the ID of the item. Note that this
                        property is optional for selector controls and that the meaning of the value
                        depends on the specifc subclass being queried.
*/
enum
{
    kAudioSelectorControlPropertyCurrentItem    = 'scci',
    kAudioSelectorControlPropertyAvailableItems = 'scai',
    kAudioSelectorControlPropertyItemName       = 'scin',
    kAudioSelectorControlPropertyItemKind       = 'clkk'
};

/*!
    @enum           Constants for the value of the property, kAudioSelectorControlPropertyItemKind 
                    for any selector control item
    @constant       kAudioSelectorControlItemKindSpacer
                        This ID represents an item in a selector control's range that represents a
                        spacer item in a pop-up menu. Items with this kind are not be selectable.
*/
enum
{
    kAudioSelectorControlItemKindSpacer = 'spcr'
};

/*!
    @enum           Constants for the value of the property, kAudioSelectorControlPropertyItemKind
                    for AudioClockSourceControls.
    @constant       kAudioClockSourceItemKindInternal
                        This ID represents the device's internal clock.
*/
enum
{
    kAudioClockSourceItemKindInternal   = 'int '
};

//==================================================================================================
#pragma mark -
#pragma mark AudioStereoPanControl Constants

/*!
    @enum           AudioStereoPanControl Class Constants
    @abstract       Various constants related to the AudioStereoPanControl class.
    @constant       kAudioStereoPanControlClassID
                        The AudioClassID that identifies the StereoPanControl class.
*/
enum
{
    kAudioStereoPanControlClassID   = 'span'
};

/*!
    @enum           AudioStereoPanControl Property Selectors
    @abstract       AudioObjectPropertySelector values provided by the AudioStereoPanControl class.
    @discussion     The AudioStereoPanControl class is a subclass of the AudioControl class and has
                    the same scope and element structure.
    @constant       kAudioStereoPanControlPropertyValue
                        A Float32 where 0.0 is full left, 1.0 is full right, and 0.5 is center.
    @constant       kAudioStereoPanControlPropertyPanningChannels
                        An array of two UInt32s that indicate which elements of the device the
                        signal is being panned between.
*/
enum
{
    kAudioStereoPanControlPropertyValue             = 'spcv',
    kAudioStereoPanControlPropertyPanningChannels   = 'spcc'
};

//==================================================================================================

#if defined(__cplusplus)
}
#endif

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#endif  //  __AudioHardwareBase_h__
