require "socket"

server = TCPServer.open(12345)
puts 'サーバが待機中(ポート番号12345)'
socket = server.accept
puts 'クライアントが接続しました'

while buf = socket.gets
  puts "#{buf}"
end

puts '接続を終了します'
socket.close
server.close