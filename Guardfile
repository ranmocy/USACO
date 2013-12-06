guard 'shell' do
  watch(/(\w*).(c|in)$/) do |m|
    name = m[1]
    puts `gcc -Wall -o #{name}.run #{name}.c 2>&1`
    puts `time ./#{name}.run 2>&1`
    puts `cat #{name}.out`
  end
end
