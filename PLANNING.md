# Milestones

## "Hello, world"

+   *Objective:* Run the smallest piece of code that can give back any kind of feedback
+   *Example Code:*

        public class Example {
            static {
                System.exit(99);
            }
        }

+   *Reasonings:*
    + We avoid unecessary interactions to (and from) VM, by applying the Hollywood principle "don't call us, we call you".
    + To avoid reflections and calls from outside VM, we use a static initializer. 
    + Feedback is pretty simple, requiring a single class "linkage" and one static invoke
    + Automatic tests can be as simple as "check if exit status of VM is 99".
    + Intermediate tests can be easily achieved on a feature-by-feature base
+   *Expected New Features:*
    + Read a class file
    + Read Java bytecodes
    + JIT
    + Start VM
    + Invoke class initializers
    + Create a wrapper for Object
    + Create a wrapper for System
    + Call VM from Java
    + Interrupt VM using Java
+   *Caveats:*
    + There's a lot to be done, but this version will be as MVP as possible. This means milestone will be "reached" if that specific example pass.
    + At the end of this milestone, we will probably have only an empty Object and a System with only one method. This will work, since Java linkage only care about methods listed on the class file.

