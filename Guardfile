require 'colorize'

guard 'shell' do
  watch(/^(?!flycheck)(\w*).(c|in)$/) do |m|
    name = m[1]
    puts `gcc -g -Wall -o #{name}.run #{name}.c 2>&1`.red
    puts `time ./#{name}.run 2>&1`.yellow
    puts `cat #{name}.out`.green
  end
end
