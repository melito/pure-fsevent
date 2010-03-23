require 'mkmf'

dir_config("stream")

with_ldflags("-framework CoreServices") do
  create_makefile("stream")
end
