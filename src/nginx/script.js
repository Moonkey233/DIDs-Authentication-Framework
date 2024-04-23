const texts = [
	["Hello, 欢迎来到我的DID & VCs身份认证框架", ""],
	["这个框架包括区块链管理模块", "这个框架包括"],
	["区块链浏览器模块", ""],
	["还包括DID与用户、合约管理模块", "还包括"],
	["一个DID & VCs 开发样例demo", ""],
	["以及······", "以及"],
	["一个RestService API", ""],
	["欢迎测试使用！^_^", ""]
];
const typingDiv = document.getElementById('typing');
let textIndex = 0;
let charIndex = 0;
let isAdding = true;
let delay = 100;

function playTyping() {
	if (isAdding) {
		if (charIndex <= texts[textIndex][0].length) {
			typingDiv.textContent += texts[textIndex][0][charIndex++];
			delay = Math.max(30, 120 - 90 * charIndex / texts[textIndex][0].length);  // 打字速度
		}
		if (charIndex === texts[textIndex][0].length) {
			isAdding = false;
			delay = 1500; // 等待一段时间后开始删除
		}
	} else {
		if (typingDiv.textContent !== texts[textIndex][1]) {
			typingDiv.textContent = typingDiv.textContent.substring(0, texts[(textIndex + texts.length - 1) % texts.length][1].length + charIndex--);
			delay = 50;  // 删除速度更快
		}
		if (typingDiv.textContent === texts[textIndex][1] || typingDiv.textContent === "") {
			isAdding = true;
			textIndex = (textIndex + 1) % texts.length; // 循环文本数组
			charIndex = 0; // 重置字符索引
		}
	}
	setTimeout(playTyping, delay);
}

document.addEventListener('DOMContentLoaded', function () {
    const themeToggle = document.getElementById('theme-toggle');
    if (themeToggle) {
        themeToggle.addEventListener('click', function() {
            document.body.classList.toggle('dark-mode');
            const buttons = document.querySelectorAll('.button');
            buttons.forEach(button => {
                button.classList.toggle('dark-mode');
            });
        });
    }

    // Rest of your playTyping code here
    playTyping();
});
