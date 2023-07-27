const superagent = require('superagent');
const host = 'www.luogu.com.cn';

async function getCaptcha(path) {
    var res = await superagent.get(`https://${host}/`);
    var cookie = res.headers['set-cookie'];
    var captcha = await superagent
        .get(`https://${host}/api/verify/captcha?_t=${new Date().getTime()}`)
        .set('Cookie', cookie);
    fs.writeFileSync("captcha.png", captcha.body, "binary");
    return cookie;
}

async function Login(options) {
    var { username, password, captcha, cookie } = options;
    var res = await superagent
        .post(`https://${host}/api/auth/userPassLogin`)
        .set('Cookie', cookie)
        .send({ username, password, captcha });
    return res;
}

module.exports = { Login, getCaptcha };