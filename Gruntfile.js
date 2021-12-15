'use strict';

module.exports = function(grunt) {

  // Project configuration.
  grunt.initConfig({
    // Before generating any new files, remove any previously-created files.
    clean: {
      build: ['firmware']
    },
	
	copy: {
	  main: {
		files: [
        // includes files within path and its sub-directories
        {
          expand: true, cwd: 'src/processy', src: '**', dest: 'firmware/'
        },
        // includes files within path and its sub-directories
        {
          expand: true, cwd: 'src/firmware', src: '**', dest: 'firmware/'
        }
		  ]
		}
	},
	
	run: {
		build_sketch: {
			exec: '"e:/Projects/!DIY/Arduino/IDE/arduino-cli.exe" compile --fqbn arduino:avr:nano firmware',
		},
		upload_sketch: {
			exec: '"e:/Projects/!DIY/Arduino/IDE/arduino-cli.exe" upload -p COM5 --fqbn arduino:avr:nano firmware'
		}
	},

    // Configuration to be run (and then tested).
    "grunt-h2cpp-parser": {
      parsesrc: {
        files: {
          'firmware': ['src/processy/*.h','src/firmware/*.h']
        }
      }
    }
  });

  // Actually load this plugin's task(s).
  grunt.loadTasks('tasks');

  // These plugins provide necessary tasks.
  grunt.loadNpmTasks('grunt-contrib-clean');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-run');

  // Whenever the "test" task is run, first clean the "tmp" dir, then run this
  // plugin's task(s), then test the result.
  //grunt.registerTask('test', ['clean', 'grunt-h2cpp-parser']);
  
  grunt.registerTask('build', ['clean','copy','grunt-h2cpp-parser','run:build_sketch']);
  grunt.registerTask('upload', ['run:upload_sketch']);

  // By default, lint and run all tests.
  grunt.registerTask('default', ['build','upload']);
};
