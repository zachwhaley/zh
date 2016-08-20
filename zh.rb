#!/usr/bin/env ruby

require 'shellwords'

BUILTINS = {
  'cd' => lambda { |dir| Dir.chdir(dir) },
  'exit' => lambda { exit 0 },
}

loop do
  # Print prompt
  print 'ζ '
  # Get command
  cmd = $stdin.gets.strip
  next if cmd.empty?

  # Parse command
  prog, *args = Shellwords.shellsplit(cmd)
  if BUILTINS[prog]
    # Call builtin command
    BUILTINS[prog].call(*args)
  else
    # Fork and exec command
    pid = fork { exec(prog, *args)  }
    Process.wait pid
  end
end
