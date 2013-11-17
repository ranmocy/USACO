guard 'shell' do
  watch(/(\w*).c$/) do |m|
    name = m[1]
    puts `gcc -Wall -o #{name}.run #{name}.c`
    puts `./#{name}.run`
    puts `cat #{name}.out`
  end
end
