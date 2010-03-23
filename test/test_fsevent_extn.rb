require "test_helper"
$:.unshift File.dirname(__FILE__) + "/../ext/fsevent"
require "fsevent.so"

class TestFseventExtn < MiniTest::Unit::TestCase

  def setup
    @watcher = FSEvent.new("/tmp" => "echo 'YES'")
  end

  def test_we_can_only_create_with_hashes
    assert_raises(TypeError) { FSEvent.new("hi") }
    assert_raises(ArgumentError) { FSEvent.new }
  end

  def test_directories_accessor
    refute_nil   @watcher.directories
    refute_empty @watcher.directories
    assert_equal @watcher.directories, ["/tmp"]
  end

  def test_weird_input
    watcher = FSEvent.new({})
    refute_nil watcher.directories
    assert_empty watcher.directories
  end

  def test_for_streams
    refute_nil @watcher.streams
  end

end
