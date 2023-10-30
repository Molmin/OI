import { existsSync } from 'fs';
import FSExtra from 'fs-extra';
import randomString from 'string-random';

export function backupFile(opId, path, isDir) {
    if (!existsSync(`data/${path}`)) return;
    FSExtra.ensureDirSync(`data/backup/${opId}`);
    if (!isDir && path.lastIndexOf("/") >= 0)
        FSExtra.ensureDirSync(`data/backup/${opId}/${path.
            substr(0, path.lastIndexOf("/"))}`);
    if (isDir) FSExtra.ensureDirSync(`data/backup/${opId}/${path}`);
    FSExtra.copySync(`data/${path}`, `data/backup/${opId}/${path}`);
}

export function newOperationId() {
    return randomString(8);
}