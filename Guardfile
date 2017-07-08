require 'colorize'

TIME_CMD = (/darwin/ =~ RUBY_PLATFORM) ? '/usr/bin/time -l' : '/usr/bin/time -v'

guard 'shell' do
  watch(/^(?!flycheck)(\w*).(c|in)$/) do |m|
    name = m[1]
    next unless File.exists?("#{name}.c")
    puts `gcc -O2 -Wall -o #{name}.run #{name}.c 2>&1`.red
    puts `#{TIME_CMD} ./#{name}.run 2>&1`.yellow if $? == 0
    puts `cat #{name}.out`.green if $? == 0
    `rm #{name}.run #{name}.out 2>/dev/null`
  end

  watch(/^(?!flycheck)(\w*).(cpp|in)$/) do |m|
    name = m[1]
    next unless File.exists?("#{name}.cpp")
    puts `g++ -O2 -Wall -lm -std=c++0x -o #{name}.run #{name}.cpp 2>&1`.red
    puts `#{TIME_CMD} ./#{name}.run 2>&1`.yellow if $? == 0
    puts `cat #{name}.out`.green if $? == 0
    `rm #{name}.run #{name}.out 2>/dev/null`
  end
end
