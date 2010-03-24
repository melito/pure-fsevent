#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h> // Seriously?  Seriously.

void myCallbackFunction(
			ConstFSEventStreamRef streamRef,
			void *context,
			size_t numEvents,
			void *eventPaths,
			const FSEventStreamEventFlags eventFlags[],
			const FSEventStreamEventId eventIds[]) {
  VALUE self = (VALUE)context;
  
  // FIXME: Read the docs and figure out something clever to do with this.  Dummy.
  int i;
  char **paths = eventPaths;
  VALUE rb_paths[numEvents];
  for (i = 0; i < numEvents; i++) {
    VALUE name = rb_str_new2(paths[i]);
    rb_paths[i] = name;
  }

  VALUE callback = rb_iv_get(self, "@callback");
  switch(TYPE(callback)) {
  case T_STRING:
    printf("Executing: %s\r\n", RSTRING_PTR(callback));
    //execvp(RSTRING_PTR(callback), (char *)0 );
    system(RSTRING_PTR(callback));
    break;
  case T_REGEXP:
    printf("I don't support regexp's yet because I'm not very good at this.  Sorry.\r\n");
    rb_raise("NotImplemented", "I haven't built this yet, damnit.");
    break;
  default:
    rb_raise(rb_eTypeError, "callback is not a valid value");
    break;
  }
  

}


VALUE t_create(VALUE self){
  
  VALUE path = rb_iv_get(self, "@path");
  CFStringRef mypath = CFStringCreateWithCString(NULL, (char *)RSTRING_PTR(path), kCFStringEncodingUTF8);

  CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&mypath, 1, NULL);
  FSEventStreamRef stream;
  CFAbsoluteTime latency = 0.5; /* Latency in seconds */

  FSEventStreamContext context;
  context.version = 0;
  context.info = (VALUE *)self;
  context.retain = NULL;
  context.release = NULL;
  context.copyDescription = NULL;

  stream = FSEventStreamCreate(NULL,
			       &myCallbackFunction,
			       &context,
			       pathsToWatch,
			       kFSEventStreamEventIdSinceNow, /* Or a previous event ID */
			       latency,
			       kFSEventStreamCreateFlagNone /* Flags explained in reference */
			       );

  FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
  FSEventStreamStart(stream);

  return Qtrue;
}

VALUE t_init(VALUE self, VALUE path, VALUE callback){
  rb_iv_set(self, "@path", path);
  rb_iv_set(self, "@callback", callback);
  return Qtrue;
}

void Init_stream(){ 
  VALUE stream_class = rb_define_class("Stream", rb_cObject);
  rb_define_method(stream_class, "initialize", t_init, 2);
  rb_define_method(stream_class, "create", t_create, 0);

  rb_define_attr(stream_class, "path", 1, 0);
}
