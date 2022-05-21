import fs from 'fs'
import util from 'util'
import child_process from 'child_process'
import chalk from 'chalk'

const exec = util.promisify(child_process.exec)

function getCompileCmd(name, ext) {
  switch (ext) {
    case 'c':
      return `gcc -O2 -Wall -o ${name}.run ${name}.c`
    case 'cpp':
      return `g++ -O2 -Wall -lm -std=c++0x -o ${name}.run ${name}.cpp`
    default:
      return
  }
}

async function runCmd(label, cmd) {
  try {
    const result = await exec(cmd)
    if (result.stdout) console.log(chalk.green(`${label}: ${result.stdout}`))
    if (result.stderr) console.error(chalk.red(`${label}: ${result.stderr}`))
    return true
  } catch (e) {
    console.error(chalk.red(`${label} failed: code: ${e.code}, message: ${e.message}.`))
    return false
  }
}

let lastFileChanged = 0
fs.watch('.', {}, async (eventType, fileName) => {
  // Ignore dupliate events
  if (Date.now() - lastFileChanged < 100) {
    return
  }
  lastFileChanged = Date.now()

  // Only files with selected ext names
  const m = fileName.match(/^(?!flycheck)(\w*).(c|cpp|in)$/)
  if (!m) {
    return
  }

  // Redirect .in file to source file
  let name = m[1], ext = m[2]
  console.log(`File ${eventType}: ${name}.${ext}`)
  if (fs.existsSync(`${name}.c`)) {
    ext = 'c'
  } else if (fs.existsSync(`${name}.cpp`)) {
    ext = 'cpp'
  } else {
    console.log(`No target source file, ignore`)
    return
  }

  // Compile, run, output
  if (!await runCmd('Compile', getCompileCmd(name, ext))) return
  // TIME_CMD = (/darwin/ =~ RUBY_PLATFORM) ? '/usr/bin/time -l' : '/usr/bin/time -v'
  if (!await runCmd('Run', `/usr/bin/time -l ./${name}.run 2>&1`)) return
  if (!await runCmd('Output', `cat ${name}.out`)) return

  // Cleanup
  const cleanupCallback = (err) => { if (err) console.error(chalk.red(`Cleanup failed:`), err) }
  fs.rm(`${name}.run`, cleanupCallback)
  fs.rm(`${name}.out`, cleanupCallback)
})
