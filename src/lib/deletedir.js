import { existsSync, readdirSync, statSync, unlinkSync, rmdirSync } from 'fs';
import { join } from 'path';

var deletedir = (url) => {
    if (existsSync(url)) {
        var files = [];
        files = readdirSync(url);
        files.forEach(file => {
            var curPath = join(url, file);
            if (statSync(curPath).isDirectory())
                deletedir(curPath);
            else unlinkSync(curPath);
        });
        rmdirSync(url);
    }
};

export default deletedir;