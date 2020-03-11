const readline = require('readline')
const compilePatternMatcher = require('./lib/patternMatcher')

if (process.argv.length !== 3) {
    console.log("usage: find pattern")
    return -1
}

const patternString = process.argv[2]

try {
    const matcher = compilePatternMatcher(patternString)

    const rl = readline.createInterface({ input: process.stdin })

    rl.on('line', line => matcher.test(line) && console.log(line))
} catch (e) {
    console.error(`OOPS! ${ex.message}`)
    return -1
}