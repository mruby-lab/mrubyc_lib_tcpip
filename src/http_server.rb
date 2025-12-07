# require 'socket'

server = TCPServer.open(80)  # サーバー起動
puts "Server started http://localhost/"

loop do
  socket = server.accept     # 接続待ち
  request = socket.recv(1024) # 受信

  puts "Request: #{request}"

  body = "<h1>Hello World!</h1>"
  response = <<~R
    HTTP/1.1 200 OK
    Content-Type: text/html; charset=UTF-8
    Content-Length: #{body.size}

    #{body}
  R

  socket.send(response, 0)   # 返信（sendは許可されてる想定）

  socket.close               # 切断

end

server.close
