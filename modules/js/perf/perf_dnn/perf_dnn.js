const isNodeJs = (typeof window) === 'undefined'? true : false;

if　(isNodeJs)　{
  var Benchmark = require('benchmark');
  var cv = require('../../opencv');
  var HelpFunc = require('../perf_helpfunc');
  var Base = require('../base');
} else {
  var paramsElement = document.getElementById('params');
  var runButton = document.getElementById('runButton');
  var logElement = document.getElementById('log');
}

createFileFromUrl = function(path, url, callback) {
  let request = new XMLHttpRequest();
  request.open('GET', url, true);
  request.responseType = 'arraybuffer';
  request.onload = function(ev) {
      if (request.readyState === 4) {
          if (request.status === 200) {
              let data = new Uint8Array(request.response);
              cv.FS_createDataFile('/', path, data, true, false, false);
              callback();
          } else {
              console.error('Failed to load ' + url + ' status: ' + request.status);
          }
      }
  };
  request.send();
};

// get name of model and config file from url
function getNameFromUrl(url) {
  const modelParts = url.modelUrl.split('/');
  const modelPath = modelParts[modelParts.length-1];
  const configParts = url.configUrl.split('/');
  const configPath = configParts[configParts.length-1];
  return {
      modelPath: modelPath,
      configPath: configPath
  }
}

let modelLoaded = [];
loadModel = async function(url) {
  path = getNameFromUrl(url);
  return new Promise((resolve) => {
      // check if the model has been loaded before
      if(modelLoaded.indexOf(path.modelPath) == -1){
          createFileFromUrl(path.modelPath, url.modelUrl, () => {
              modelLoaded.push(path.modelPath);
              // check if need to load config file
              if(url.configUrl !== "") {
                  createFileFromUrl(path.configPath, url.configUrl, () => {
                      resolve(path);
                  });
              } else {
                  resolve(path);
              }
          });
      } else {
          resolve(path);
      }
  });
}

async function processNet(weights, proto, size)
{
    const url = {
        modelUrl: weights,
        configUrl: proto
      }; 
      const path = await loadModel(url);
      const input = new cv.Mat(size, cv.CV_32F);
      net = cv.readNetFromCaffe(path.configPath, path.modelPath);
      net.setInput(input);
      net.forward();    // warm up

      let start = performance.now();
      net.forward();
      let time = performance.now() - start;

      log(`Compute model: ${path.configPath} cost ${time.toFixed(3)} ms`);
      input.delete();
      net.delete();
}

async function processNets()
{
    const prototxt1 = "layer_convolution.prototxt";
    const caffemodel1 = "layer_convolution.caffemodel";
    const size1 = [2, 6, 75, 113];
    processNet(caffemodel1, prototxt1, size1);
}

async function perf() {
    console.log('opencv.js loaded');
    if (isNodeJs) {
      global.cv = cv;
      global.combine = HelpFunc.combine;
      global.cvtStr2cvSize = HelpFunc.cvtStr2cvSize;
      global.cvSize = Base.getCvSize();
    } else {
      enableButton();
    }
    if (isNodeJs) {
        await processNets();
      } else {
        runButton.onclick = async function()　{
            await processNets();
        }
      }
}

async function main() {
    if (cv instanceof Promise) {
      cv = await cv;
      await perf();
    } else {
      cv.onRuntimeInitialized = perf;
    }
  }
  
  main();