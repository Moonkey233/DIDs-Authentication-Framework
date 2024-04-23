
#!/bin/bash

set -e

port=5101
db_url="jdbc:mysql://127.0.0.1:3306/db_browser?useUnicode=true&characterEncoding=utf8"
db_user=test
db_password=123456
cdn_download_link="https://osp-1257653870.cos.ap-guangzhou.myqcloud.com/FISCO-BCOS/fisco-bcos-browser/releases/download/v2.2.1-Integrated/fisco-bcos-browser.zip"
package_name=fisco-bcos-browser.zip
current_dir=$(pwd)

LOG_WARN()
{
    local content=${1}
    echo -e "\033[31m[WARN] ${content}\033[0m"
}

LOG_INFO()
{
    local content=${1}
    echo -e "\033[32m[INFO] ${content}\033[0m"
}

help() {
    cat << EOF
Usage:
    -P <Port>                           Default 5101
    -l <DB url>       	                Default jdbc:mysql://127.0.0.1:3306/db_browser?useUnicode=true&characterEncoding=utf8
    -u <DB user>                        Default test
    -P <DB password>                    Default 123456
    -h Help
e.g
    $0 -P 5101 -l jdbc:mysql://127.0.0.1:3306/db_browser?useUnicode=true&characterEncoding=utf8 -u test -p 123456
EOF

exit 0
}

parse_params()
{
while getopts "P:l:u:p:h" option;do
    case $option in
    P) port=$OPTARG;;
    l) db_url=$OPTARG;;
    u) db_user=$OPTARG;;
    p) db_password=$OPTARG;;
    h) help;;
    esac
done

}

clean_with_msg()
{
    local content=${1}
    echo -e "\033[31m[ERROR] ${content}\033[0m"
    exit 1
}

exit_with_msg()
{
    local content=${1}
    echo -e "\033[31m[ERROR] ${content}\033[0m"
    exit 1
}

check_port()
{
	echo "Checking port"
	pIDa=`lsof -i :$port|grep -v "PID" | awk '{print $2}'`
	if [ "$pIDa" != "" ];
	then
	   exit_with_msg "${port} is already binded! Please check!"
	else
	   echo "port check passed."
	fi
}

check_JAVA_HOME()
{
	echo "Checking JAVA_HOME"
	if   [   $JAVA_HOME   ]; 
	then 
		echo "JAVA_HOME check passed."
	else 
		exit_with_msg "JAVA_HOME is ${JAVA_HOME}!"
	fi
}

download_bin()
{
	curl -#LO "${cdn_download_link}"
    unzip ${package_name} > /dev/null 2>&1 
	rm ${package_name}
	mv ./server/conf/application.yml ./server/conf/application.yml$(date +%Y%m%d-%H%M%S) 
}

generate_config_ini()
{
    local output=${1}
    cat << EOF > "${output}"
server: 
  port: ${port}
  context-path: /fisco-bcos-browser

spring: 
  datasource: 
    url: ${db_url}
    username: ${db_user}
    password: ${db_password}
    driver-class-name: com.mysql.jdbc.Driver
  
mybatis:  
  mapper-locations: classpath:mapper/*.xml  

constant: 
  configAuth: true
  cronBlockChainInfo: 0/10 * * * * ?
  cronBlockInfo: 0/10 * * * * ?
  cronTxnByDay: 30 0/1 * * * ?
  cronAyncNode: 0 0/10 * * * ?
  cronIfNodeActive: 0 0/1 * * * ?
  cronDeleteTxn: 0 0/10 * * * ?
  handleBlocks: 50
  keepTxnCnt: 500000
  
logging: 
  config: classpath:log4j2.xml
EOF

}


LOG_INFO "init fisco-bcos-browser"
LOG_INFO "=============================================================="
parse_params $@
check_port
check_JAVA_HOME
download_bin
generate_config_ini "./server/conf/application.yml"
LOG_INFO "=============================================================="
LOG_INFO "All completed. "
exit 
