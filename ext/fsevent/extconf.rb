require 'mkmf'

# I test with Clang.  It's a lot better at C than I am.
# CC=/Developer/usr/bin/clang rake compile
RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

dir_config("fsevent")
with_ldflags("-framework CoreServices") do
  create_makefile("fsevent")
end
