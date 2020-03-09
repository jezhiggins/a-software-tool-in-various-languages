const readline = require('readline')
const patternMatcher = require('./lib/patternMatcher')

if (process.argv.length !== 3) {
    console.log("usage: find pattern")
    return -1
}

try {
    const matcher = patternMatcher(process.argv[2])

    const rl = readline.createInterface({ input: process.stdin })

    rl.on('line', line => matcher.test(line) && console.log(line))
} catch (e) {
    console.error(`OOPS! ${ex.message}`)
    return -1
}