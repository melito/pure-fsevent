#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <CoreServices/CoreServices.h>

VALUE t_run(VALUE self){
  CFRunLoopRun();
}

VALUE t_init(VALUE self, VALUE watch_action_list){
  Check_Type(watch_action_list, T_HASH);
  rb_iv_set(self, "@directories", rb_funcall(watch_action_list, rb_intern("keys"), 0));
  rb_iv_set(self, "@streams", rb_ary_new());

  return self;
}

void Init_fsevent(){

  VALUE fsevent_class = rb_define_class("FSEvent", rb_cObject);
  rb_define_method(fsevent_class, "initialize", t_init, 1);
  rb_define_method(fsevent_class, "run", t_run, 0);

  rb_define_attr(fsevent_class, "directories", 1, 1);
  rb_define_attr(fsevent_class, "streams", 1, 0)
}
