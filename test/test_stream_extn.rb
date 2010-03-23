require "test_helper"
$:.unshift File.dirname(__FILE__) + "/../ext/stream"
require "stream.so"

class TestStreamExtn < MiniTest::Unit::TestCase

  def setup
    @stream = Stream.new("/tmp", "rake")
  end

  def test_simple
    refute_nil @stream
    assert_kind_of Stream, @stream
  end

  def test_has_path
    refute_nil   @stream.path
    refute_empty @stream.path
    assert_equal @stream.path, "/tmp"
  end

  def test_can_create_event_stream
    assert_respond_to @stream, :create
    refute_nil @stream.create
  end

end
