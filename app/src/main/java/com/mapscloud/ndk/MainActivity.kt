package com.mapscloud.ndk

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.mapscloud.libnativemate.assimp.MyGLSurfaceView
import com.mapscloud.libnativemate.assimp.SceneView
import com.mapscloud.ndk.utils.PermissionsUtils

class MainActivity : AppCompatActivity() {
    private lateinit var permissionsUtils: PermissionsUtils
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        permissionsUtils = PermissionsUtils.getInstance(this) {
            setContentView(
                MyGLSurfaceView(
                    this
                )
            )
        }
        permissionsUtils.checkSelfPermission()
    }


    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        permissionsUtils.onActivityResult(requestCode)
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        permissionsUtils.onRequestPermissionsResult(requestCode, permissions, grantResults)
    }
}