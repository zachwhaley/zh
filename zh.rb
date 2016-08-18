#!/usr/bin/env ruby

loop do
  # Print prompt
  print 'ζ '
  # Get command
  cmd = $stdin.gets.strip
  next if cmd.empty?
  # Fork and exec command
  pid = fork { exec cmd }
  Process.wait pid
end
