require File.dirname(__FILE__) + "/lib/pure-fsevent"

jobs_list = {"/tmp" => "echo 'tmp' changed",
             "/etc" => "echo 'etc' changed"}

watchr = FSEvent.new(jobs_list)

p watchr.directories
p watchr.streams

watchr.run
