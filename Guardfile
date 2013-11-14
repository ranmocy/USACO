guard 'shell' do
  watch(/(.*).c$/) do |m|
    name = m[1]
    puts `gcc -Wall -o #{name}.run #{name}.c`
    `./#{name}.run`
    puts `cat #{name}.out`
  end
end
