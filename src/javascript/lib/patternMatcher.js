
function patternMatcher(pattern) {
    let fixedUpPattern = ''
    let escaped = false
    let classStart = false

    for (let i = 0; i != pattern.length; ++i) {
        const c = pattern[i]

        if (c === '%') {
            fixedUpPattern += (i !== 0) ? c : '^'
            continue
        }

        if (c === '@' && !escaped) {
            escaped = true
            fixedUpPattern += '\\'
            continue
        }

        if (c === '?' && !escaped) {
            fixedUpPattern += '.'
            continue
        }

        if ('\\+.'.includes(c)) {
            fixedUpPattern += '\\' + c
            continue
        }

        if (c === '^' && !classStart) {
            fixedUpPattern += '\\^'
            continue
        }

        classStart = (c === '[')
        escaped = false
        fixedUpPattern += c
    }

    return new RegExp(fixedUpPattern)
}

module.exports = patternMatcher