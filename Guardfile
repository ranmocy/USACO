require 'colorize'

guard 'shell' do
  watch(/^(?!flycheck)(\w*).(c|in)$/) do |m|
    name = m[1]
    puts `gcc -O2 -Wall -o #{name}.run #{name}.c 2>&1`.red
    puts `time ./#{name}.run 2>&1`.yellow
    puts `cat #{name}.out`.green
    `rm #{name}.run #{name}.out`
  end

  watch(/^(?!flycheck)(\w*).(cpp|in)$/) do |m|
    name = m[1]
    puts `g++ -O2 -Wall -o #{name}.run #{name}.cpp 2>&1`.red
    puts `time ./#{name}.run 2>&1`.yellow
    puts `cat #{name}.out`.green
    `rm #{name}.run #{name}.out`
  end
end
