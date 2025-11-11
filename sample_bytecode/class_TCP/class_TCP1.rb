# require "socket"

# ip = "192.168.128.181"
port = 12345

# ip = Socket.ip_address_list.find do |addr|
#   addr.ipv4_private?
# end&.ip_address
# puts "このPCのIPアドレス: #{ip}"

server = TCPServer.open(port)
puts "サーバが待機中(ポート番号#{port})"
socket = TCPServer.accept
puts 'クライアントが接続しました'

while buf = TCPServer.recv(100)
  puts '文字列を受信しました'
  puts "#{buf}"

  TCPSocket.send(buf, 0)
  puts '文字列を送信しました' 
end

puts '接続を終了します'
TCPServer.close
# server.close