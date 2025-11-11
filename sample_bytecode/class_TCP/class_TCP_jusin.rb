#require "socket"

server = TCPServer.open(12345)
puts 'サーバが待機中(ポート番号12345)'
socket = TCPServer.accept
puts 'クライアントが接続しました'

while buf = TCPServer.recv(100)
  puts "#{buf}"
end

puts '接続を終了します'
TCPServer.close
# server.close