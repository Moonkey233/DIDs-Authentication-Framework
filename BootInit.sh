service mysqld start  # MySQL
cd /root/fisco/nodes/127.0.0.1  # Nodes
bash start_all.sh
cd /root/fisco/console/webase-deploy  # WeBASE
python3 deploy.py startAll
cd /root/did/weid-build-tools  # WeIdentity
bash start.sh
cd /root/did/browser-deploy/server  # Fisco browser
bash start.sh
cd /root/restService/WeIdentity-Rest-Service/dist  # RestService
bash start.sh
cd /root/did/WeIdentity-Sample-3.1.0  # DID Simple
bash start.sh
cd /root/nginx  # Nginx
nginx -c /root/nginx/nginx.conf
# cd /root/clash/clash-for-linux-backup  # Clash
# bash start.sh
# source /etc/profile.d/clash.sh
cd /root
free -m
# echo "请执行以下命令开启系统代理: proxy_on"
# echo "若要临时关闭系统代理, 请执行: proxy_off"