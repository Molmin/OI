const fs = require('fs');
const fse = require('fs-extra');
const randomString = require('string-random');

function backupFile(opId, path, isDir) {
    if (!fs.existsSync(`data/${path}`)) return;
    fse.ensureDirSync(`data/backup/${opId}`);
    if (!isDir && path.lastIndexOf("/") >= 0)
        fse.ensureDirSync(`data/backup/${opId}/${path.
            substr(0, path.lastIndexOf("/"))}`);
    if (isDir) fse.ensureDirSync(`data/backup/${opId}/${path}`);
    fse.copySync(`data/${path}`, `data/backup/${opId}/${path}`);
}

function newOperationId() {
    return randomString(8);
}

module.exports = { backupFile, newOperationId };