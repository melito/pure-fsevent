$:.unshift(File.dirname(__FILE__)) unless
  $:.include?(File.dirname(__FILE__)) || $:.include?(File.expand_path(File.dirname(__FILE__)))

require "ext/fsevent/fsevent.bundle"
require "ext/stream/stream.bundle"

module PureFsevent
  VERSION = '0.0.1'
end
