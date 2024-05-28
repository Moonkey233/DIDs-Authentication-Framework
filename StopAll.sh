cd /root/fisco/nodes/127.0.0.1  # Nodes
bash stop_all.sh
cd /root/fisco/console/webase-deploy  # WeBASE
python3 deploy.py stopAll
cd /root/did/weid-build-tools  # WeIdentity
bash stop.sh
cd /root/did/browser-deploy/server  # Fisco browser
bash stop.sh
cd /root/restService/WeIdentity-Rest-Service/dist  # RestService
bash stop.sh
cd /root/did/WeIdentity-Sample-3.1.0  # DID Simple
bash stop.sh
cd /root/nginx  # Nginx
nginx -c /root/nginx/nginx.conf -s stop
cd /root/clash/clash-for-linux-backup  # Clash
bash shutdown.sh
service mysqld stop  # MySQL
cd /root
free -m
echo "服务关闭成功, 请执行以下命令关闭系统代理: proxy_off"