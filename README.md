# espresso

A small subset of a Java Virtual Machine that can be embedded in another language.

## Reasoning

Have you ever tried to embed a JVM inside another process? I'm not talking about using Java on embedded systems (which is the focus of [Java Embedded](http://docs.oracle.com/javase/8/javase-embedded.htm)). I'm talking about starting, managing and stopping a JVM inside another process. That's a common (and straighforward) process for other technologies, like Lua, JavaScript, Python, or even Perl, but it's a insane crusade for Java. Why? At least, those reasons:

+ Oracle's JVM hijacks all SysV signals (SIGSEGV, SIGUSR, etc). That cripples any debug attempt (you have to ignore signals, since every NullPointerException possible results in a SIGSEGV)
+ There's no way to control the JVM memory allocations (you can barely limit heap size with '-Xmx' and friends)
+ There's no way to control the GC (that deserves a whole book explaining what you can't do)
+ There's no way you can be notified when an object is deallocated
+ You cannot run two JVMs inside the same process
+ It's a pain to create "pure native" classes
+ JNI is just a mess (this also deserves a whole book)

## What to expect

+ This will be a pluggable library and I will not provide any executables - again, idea here is to provide a way to embed Java inside another language (mostly C/C++).
+ It's meant to be barebone. In a very high level, it will only provide a way to load classes and run methods. There will be basic, but exchangable, memory allocation, and GC will be done with a "retain/release" model (or "incref/decref", if you are a C/Python fan).
+ Java APIs, when implemented, will be conditionally compilable. This means you can have a "JVM" with only "java.lang", or one that can't access internet (without "java.rmi", etc).
+ I'm not following OpenJDK source or any JCP. I'll not even look at them. Only one thing will "follow the rules": the class file format. This means you can compile and test code with NetBeans, Maven, JUnit and such, then use those ".class" files with this library (JAR file is out of scope now). In a nutshell, I'll do it as binary-compatible as possible.
+ I will throw JNI out of the window. Interface with this VM will be simpler and not related at all to JNI.
+ Code will be fully JIT'ed with [https://www.gnu.org/software/dotgnu/libjit-doc/libjit_toc.html](libjit). There'll be no interpreter at all - this will probably slow loadings, but have faster runtime (and overall code will be cleaner).
+ Compilation will be managed by CMake (sorry, Autoconf fans).

## Disclaimer

This project (and myself) are not at all related to Oracle. This is also not Java, since this is a Trademark of Oracle. I also take no responsability for damages or lack of features.
