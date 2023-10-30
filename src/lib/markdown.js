import MarkdownIt from 'markdown-it'
import MarkdownItKatex from 'markdown-it-katex'
import MarkdownItImsize from 'markdown-it-imsize'
import MarkdownItFootnote from 'markdown-it-footnote'
import MarkdownItHighlightJS from 'markdown-it-highlightjs'
import MarkdownItContainer from 'markdown-it-container'

var markdown = MarkdownIt({
    html: true,
    linkify: true,
});
markdown.use(MarkdownItKatex);
markdown.use(MarkdownItImsize);
markdown.use(MarkdownItFootnote);
markdown.use(MarkdownItHighlightJS, { inline: true });

markdown.use(MarkdownItContainer, 'warning', {
    validate: (params) =>
        params.includes('note') ||
        params.includes('warning') ||
        params.includes('tip'),
    render: (tokens, idx) => {
        if (tokens[idx].nesting === 1)
            return `<blockquote class="topan-blockquote-${tokens[idx].info.substr(1)}">\n`;
        else return '</blockquote>\n';
    }
});

export default markdown