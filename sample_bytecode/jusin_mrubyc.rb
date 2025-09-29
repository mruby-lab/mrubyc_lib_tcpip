puts "Ruby start"

while true
  msg = c_server()        # C側で受信した文字列が返る
  if msg != ""            # クライアントから何か届いたときだけ処理
    puts "受信しました: #{msg}"
  end
  sleep 1                 # 無限ループでCPUを占有しないように待機
end

puts "Ruby close"