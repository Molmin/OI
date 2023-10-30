import { createHash } from 'crypto';
import { readFileSync } from 'fs';

const encode = (str) => {
  // second time
  const MD5 = createHash('md5');
  const SHA256 = createHash('sha256');
  var md5 = MD5.update(str, 'utf8').digest('hex');
  var sha256 = SHA256.update(str, 'utf8').digest('hex');
  return sha256.substr(0, 32) + md5 + sha256.substr(32);
};
export const Encode = (str) => {
  // first time
  return encode(`oiblog_${str}`);
}

export const checkloginByReq = req => req.headers.host.startsWith('localhost') || req.cookies['oiblog-cookie']
  && req.cookies['oiblog-cookie'] == Encode(readFileSync('password', 'utf8'));
  
export const checkloginByPassword = password => password == readFileSync('password', 'utf8');