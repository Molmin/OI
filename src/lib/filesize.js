module.exports = size => {
    if (size > 1024 * 1024 * 1024)
        return `${(size / 1024 / 1024 / 1024).toFixed(2)} GiB`;
    if (size > 1024 * 1024)
        return `${(size / 1024 / 1024).toFixed(2)} MiB`;
    if (size > 1024)
        return `${(size / 1024).toFixed(2)} KiB`;
    return `${size} Bytes`;
};