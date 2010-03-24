#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <CoreServices/CoreServices.h>

VALUE t_run(VALUE self){
  CFRunLoopRun();
}

void build_streams(VALUE key, VALUE val, VALUE self){
  VALUE streams = rb_iv_get(self, "@streams");

  VALUE args[2];
  args[0] = key;
  args[1] = val;
  VALUE stream = rb_class_new_instance(2, &args, rb_const_get(rb_cObject, rb_intern("Stream")));
  rb_funcall(stream, rb_intern("create"), 0);

  rb_ary_push(streams, stream);

  return ST_CONTINUE;
}

VALUE t_init(VALUE self, VALUE watch_action_list){
  Check_Type(watch_action_list, T_HASH);
  rb_iv_set(self, "@directories", rb_funcall(watch_action_list, rb_intern("keys"), 0));
  rb_iv_set(self, "@streams", rb_ary_new());

  rb_hash_foreach(watch_action_list, build_streams, self);

  return self;
}

void Init_fsevent(){

  VALUE fsevent_class = rb_define_class("FSEvent", rb_cObject);
  rb_define_method(fsevent_class, "initialize", t_init, 1);
  rb_define_method(fsevent_class, "run", t_run, 0);

  rb_define_attr(fsevent_class, "directories", 1, 1);
  rb_define_attr(fsevent_class, "streams", 1, 0);
}
