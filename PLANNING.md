# Milestones

## Milestone 4: Fields

+   *Objective:* Run the smallest piece of code that can store information inside an instance
+   *Code Rules:*
    + Simple linked list. Milestone class is a linked list node, with a value and a pointer
      to the next item.
    + A static initializer creates the list
    + A static method pass the search to the first item
    + Each item calls the next for the search
+   *Reasonings:*
    + Without fields, there's no reason for instance management - a null pointer can represent
      a world of classes without fields.
+   *Expected New Features:*
    + Fields (both static and instance)
    + Basic GC
+   *Caveats:*
    + GC is still optional. We can just leak everything and leave GC for a next milestone.

## Milestone 3: Instances

+   *Objective:* Run the smallest piece of code that can give feedback from a new instance
+   *Example Code:*

        public class Example {
            int sum(int a, int b) {
                return a + b;
            }
            static int doSum(int a, int b) {
                return new Example().sum(a, b);
            }
        }

+   *Reasonings:*
    + After previous milestones, there isn't much baby-steps we can do without instancing.
+   *Expected New Features:*
    + Instance handling
    + Instance methods (i.e. something that receives "this" as first parameter)
    + Basic GC
    + "new" and "invokevirtual"
+   *Caveats:*
    + Originally, this milestone was counting only on instance methods, but the "minimal"
      for this is the same as a class method, plus passing a "null" object. To force the
      "minimal" to contain an instance, it was changed to instantiate and use that.
    + Maybe constructors can be shamelessly ignored in this example (along with "invokespecial")

## Milestone 2: Flow control and recursive calls

+   *Objective:* Add support for flow control and recursive calls
+   *Example Code:*

        public class Example {
            static int fib(int n) {
                if (n < 2) return 1;
                return fib(n - 1) + fib(n - 2);
            }
        }

+   *Reasonings:*
    + After the previous milestone, large groups of opcodes can be easily added, except objects and flow control. The former also requires an object model. The latter, just a small refactor on JIT.
    + Recursive calls are common, and will fail with current method resolving implementation.
+   *Expected New Features:*
    + Flow control
    + Recursive calls

## Milestone 1: "Hello, world"

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

# Future milestones

