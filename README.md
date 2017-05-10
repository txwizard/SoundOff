# SoundOff

SoundOff is a simple program with a simple mission; play any sound file that is
compatible with Windows Media Player once through, then quit. It is intended for
use in batch files and other scripts.

# How It Works

**SoundOff** uses the **PlaySound** Windows Platform SDK function, defined in
** Mmsystem.h** and exported by **Winmm.dll**, to play the specified wave file. 
Intended for playing a system-defined sound, **SoundOff** is used to generate
the sound independently of any of the Windows events with which sounds are
typically associated.

Its motivation was that the common method of causing a script to play a sound
leaves a Windows Media Player window open after the sound plays. The official
documentation of [PlaySound](https://msdn.microsoft.com/en-us/library/windows/desktop/dd743680(v=vs.85).aspx)
lists and describes numerous options for identifying the sound to play. Of the 
options listed, **SoundOff** supports only file names.

# Required External DLLs

This utility requires 10 small support DLLs, which provide it with a variety of
services, such as formatting and displaying messages, rendering the machine time
when execution started, and extracting the version details from the program for
use in the logo (banner) message.

* FixedStringBuffers.dll
* P6CStringLib1.dll
* P6VersionInfo32.dll
* ProcessInfo.dll
* ReformatSysDate_P6C_FormatStrings.dll
* SafeMemCpy.dll
* WWDatelib.dll
* WWKernelLibWrapper.dll
* WWKernelLibWrapper32.dll
* WWStandardErrorMessages.dll

These are very mature DLLs that have been in daily production, on every version
of Microsoft Windows since Windows NT 4.0, and on many machines, for five to ten
years. At 12 years, WWDatelib.dll is the oldest, which is reflected in details
such as the name of its declaration header, DateLib_P6C.H, which is mismatched
with the name of the DLL, and its use of a Module Definition File, which causes
DumpBin.exe to obfuscate the entry points in reports covering dependent programs
and libraries.

# Technical Notes on the Support DLLs

The 10 support DLLs represent a great resource from which you can quickly
construct *many* useful little utilities. Since I am passing them out, you may
as well take advantage of them on their own. To that end, the **INCLUDE** directory
contains the headers that declare all of the functions exported by the ten DLLs.

All of the DLLs use either \_\_cdecl or \_\_stdcall calling conventions, and can be
called by anything that can call the Windows API. The routines that have found
their way into my VBA programs (hosted in both Excel and Word) are supplemented
by functions that have names ending in "_VB" that are true \_\_stccall equivalents
of their \_\_cdecl companions. A couple of libraries have names that end in 32;
these are upgrades of older libraries that have been fully converted to the
\_\_stdcall calling convention.

A handful of the DLLs deserve a bit more explanation.

## WDatelib.dll and ReformatSysDate_P6C_FormatStrings.dll

Libraries **WDatelib.dll** and **ReformatSysDate_P6C_FormatStrings.dll** are a pair, the
latter being a resource-only library that contains format strings for use with
one of its functions, **ReformatSysDate_P6C**. It comes with its own routine that
knows how to find and load the resource strings. The string resource IDs are
defined in **ReformatSysDate_P6C_FormatStrings.H**, which is used much as you
would the ID numbers defined in a standard *resource.h* file.

## FixedStringBuffers.dll and P6CStringLib1.dll

Libraries **FixedStringBuffers.dll** and **WWStandardErrorMessages.dll** are a
pair, and go with **FixedStringBuffers.H** and **WWStandardErrorMessages.H**,
respectively.

WWStandardErrorMessages.dll is a resource-only DLL that contains standard error
messages that I use throughout the large library of tools and custom applications
that I have created since I began working with personal computers. The resource
IDs are defined in WWStandardErrorMessages.H, which can be treated like a standard
resource.h file.

**FixedStringBuffers.dll** replaces many of the functions defined in **P6CStringLib1.dll**
with routines that work from fixed buffers that are baked into it. The functions
defined in FixedStringBuffers.dll are manifestly **not** thread-safe, since all
calls share a set of buffers. However, since there are 5 sets of buffers, it is
possible to achieve a degree of thread safety, up to maybe 4 or 5 threads, by
divvying up the buffers among the active threads.

In the unlikely event that one of these routines encounters an error, it
generates a detailed message, and stores it in a hidden buffer that is shared by
the entire library. Since it is protected by a mutex that is set when a message
is written into it, and released when the message is copied out, the error
message processing is thread-safe. So long as error reports are dispatched
quickly, this thread safety is unlikely to create contention in the real world,
since the types of problems that give rise to internal errors are unlikely to
arise in production.

**P6CStringLib1.dll** is a much older library, which deals exclusively in dynamic
memory, and is *mostly* thread-safe. Due to the way in which it acquired its current
complement of functions, the declarations are spread across numerous headers,
some of which define but a single function. **P6CStringLib1.H** pulls them all
together, and is the recommended way of importing routines from this library.
The functions are divided into logical groups, so that groups of related functions
are declared in a single header.

## SafeMemCpy.dll

**SafeMemCpy.dll** contains two functions (ANSI and Unicode), declared in
**SafeMemCpy_WW.H**, that can safely append one string to another. So long as
the conditions described in SafeMemCpy_WW.H are met, it will see to it that the
copy succeeds, even if it must allocate more memory by extending the input
buffer. It does everything in its power to succeed, and it will, unless your
machine is completely out of memory.

## WWKernelLibWrapper.dll and WWKernelLibWrapper32.dll

**WWKernelLibWrapper.dll** and **WWKernelLibWrapper32.dll** are essentially
identical. As you have probabbly guessed, WWKernelLibWrapper32.dll is an
upgrade of WWKernelLibWrapper.dll that differs mainly by following the
\_\_stdcall calling convention to the letter. Both libraries began as thin
wrappers around the heap management routines in the Windows API, to which they
bring Structured Exception Handling and, with it, better exception reporting.

The corresponding header, **WWKernelLibWrapper.H**, is intended for use with
**WWKernelLibWrapper32.dll**; WWKernelLibWrapper.dll is included only because
SafeMemCpy.dll, which has yet to be upgraded, still uses it. If you decide to
use these libraries, treat WWKernelLibWrapper.dll as deprecated, and use its
successor.
