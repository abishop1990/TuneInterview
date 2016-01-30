=begin
factorial.rb

Program to compute the factorial of a number

Written By Alan Bishop 1/28/2016
=end

#Iterative is faster than recursive so let's do that this time
def factorial(x)
    result = 1;
    for i in 1..x; result *= i; end;
    return result;
end

#Try to get from command line
x = ARGV[0].to_i

#If that doesn't work let's prompt
if(ARGV[0] == nil)
    print "Enter x value:"
    x = gets.chomp.to_i
end

puts "#{x}! = #{factorial(x)}"
